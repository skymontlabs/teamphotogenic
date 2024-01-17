#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <bredis/Connection.hpp>
#include <bredis/Extract.hpp>
#include <bredis/Markers.hpp>
#include <bredis/Result.hpp>
#include <iostream>
#include <random>

// Replace with the correct namespaces if different in your version of cpp_bredis
using boost::asio::ip::tcp;
namespace r = bredis;
using Buffer = boost::asio::streambuf;
using Iterator = boost::asio::buffers_iterator<typename Buffer::const_buffers_type, char>;

// Function to generate a random binary string
std::string generate_random_binary_string(size_t length)
{
    std::string str(length, '\0');
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, 255);

    for (auto& c : str) {
        c = static_cast<char>(distribution(generator));
    }

    return str;
}

using SuccessCallback = std::function<void(const std::string&)>;
using FailureCallback = std::function<void(const std::string&)>;


class rconn : public boost::asio::coroutine
{
    boost::asio::io_service& io_service_;
    r::Connection<tcp::socket>* redis_connection_;
    Buffer rx_buff, tx_buff;

public:
    rconn(boost::asio::io_service& is):
    io_service_(is) {}

    ~rconn()
    {
        if (redis_connection_) delete redis_connection_;
    }

    void init()
    {
        tcp::resolver resolver(io_service_);
        tcp::resolver::query query("127.0.0.1", "6379");
        auto iterator = resolver.resolve(query);

        tcp::socket socket(io_service_);
        boost::asio::connect(socket, iterator);

        redis_connection_ = new bredis::Connection<tcp::socket>(std::move(socket));
    }


#include <boost/asio/yield.hpp>
    void set_stackless(std::string key, std::string value, boost::system::error_code ec = {}, std::size_t length = 0)
    {
        reenter (this) {
            // Asynchronously write the command to the server
            yield redis_connection_->async_write(tx_buff, bredis::single_command_t("SET", key.data(), value.data()),
            [this, &key, &value](boost::system::error_code error_code, std::size_t consumed) {
                if (error_code) {
                    std::cerr << "Write error: " << error_code.message() << std::endl;
                    return;
                }
                tx_buff.consume(consumed);
                // Now that write is complete, proceed to read
                this->set_stackless(key, value, error_code, 0);
            });

            // Asynchronously read the response from the server
            yield redis_connection_->async_read(rx_buff,
            [this](boost::system::error_code error_code, auto parse_result) {
                if (error_code) {
                    std::cerr << "Read error: " << error_code.message() << std::endl;
                    return;
                }

                // Handle the response
                auto extract = boost::apply_visitor(r::extractor<Iterator>(), parse_result.result);
                if (auto *reply_str = boost::get<r::extracts::string_t>(&extract)) {
                    std::cout << "Response: " << reply_str->str << "\n";
                } else {
                    std::cout << "Non-string reply received\n";
                }

                rx_buff.consume(parse_result.consumed);
            });
        }
    }


    // Modified get_stackless2 function
    void get_stackless2(std::string key, 
                        SuccessCallback onSuccess, 
                        FailureCallback onFailure, 
                        boost::system::error_code ec = {}, 
                        std::size_t length = 0) {
        reenter (this) {
            // Asynchronously write the command to the server
            yield redis_connection_->async_write(tx_buff, 
                                                 bredis::single_command_t("GET", key.data()),
            [this, &key, onSuccess, onFailure](boost::system::error_code err, std::size_t consumed) {
                if (err) {
                    onFailure("Write error: " + err.message());
                    return;
                }
                tx_buff.consume(consumed);
                // Now that write is complete, proceed to read
                this->get_stackless2(key, onSuccess, onFailure, err, 0);
            });

            // Asynchronously read the response from the server
            yield redis_connection_->async_read(rx_buff,
            [this, onSuccess, onFailure](boost::system::error_code err, auto parse_result) {
                if (err) {
                    onFailure("Read error: " + err.message());
                    return;
                }

                // Handle the response
                auto extract = boost::apply_visitor(r::extractor<Iterator>(), parse_result.result);
                if (auto *reply_str = boost::get<r::extracts::string_t>(&extract)) {
                    onSuccess(reply_str->str);
                } else {
                    onFailure("Non-string reply received");
                }

                rx_buff.consume(parse_result.consumed);
            });
        }
    }
    
#include <boost/asio/unyield.hpp>

};

int main() {
    try {
        // Generate random binary strings for key and value
        std::string key = generate_random_binary_string(10); // 10 bytes key
        std::string value = generate_random_binary_string(20); // 20 bytes value

        boost::asio::io_service io_service;
        rconn rc(io_service);

        rc.init();

        rc.set_stackless("john",value);
        //rc.get_stackless2("john");

        // Run the io_service to perform the asynchronous operations
        io_service.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
