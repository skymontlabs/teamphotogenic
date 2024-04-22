#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <bredis/Connection.hpp>
#include <bredis/Extract.hpp>
#include <bredis/Markers.hpp>
#include <bredis/Result.hpp>
#include <iostream>
#include <random>
#include <string>
#include <string_view>



using boost::asio::ip::tcp;
namespace r = bredis;
namespace asio = boost::asio;
namespace sys = boost::system;
using Buffer = boost::asio::streambuf;
using Iterator = boost::asio::buffers_iterator<typename Buffer::const_buffers_type, char>;

class redis_connector: public boost::asio::coroutine
{
public:
    redis_connector(boost::asio::io_service& ios):
    ios_(ios),
    socket_(ios) {}

    ~redis_connector()
    {
        delete connection_;
    }

    bool connect(const std::string& host, const std::string& port)
    {
        boost::system::error_code ec;
        tcp::resolver resolver(ios_);
        auto endpoints = resolver.resolve(host, port, ec);
        if (ec) {
            std::cerr << "Resolve error: " << ec.message() << std::endl;
            return false;
        }

        boost::asio::connect(socket_, endpoints, ec);
        if (ec) {
            std::cerr << "Connect error: " << ec.message() << std::endl;
            return false;
        }

        connection_ = new bredis::Connection<tcp::socket>(std::move(socket_));

        return true;
    }




    #include <boost/asio/yield.hpp>

    bool set(const std::string& key, const std::string& value)
    {
        reenter(*this) {
            boost::system::error_code error_code;
            Buffer tx_buff, rx_buff;

            auto consumed = yield connection_->async_write(tx_buff, r::single_command_t("SET", key, value),
            [this](const sys::error_code& ec, std::size_t bytes_transferred) {
                puts("did it");
            });
            tx_buff.consume(consumed);
            if (error_code) {
                std::cerr << "Write error: " << error_code.message() << std::endl;
                return false;
            }

            auto parse_result = yield connection_->async_read(rx_buff,
            [this](const sys::error_code& ec , std::size_t bytes_transferred) {
                puts("did it");
            });
            if (error_code) {
                std::cerr << "Read error: " << error_code.message() << std::endl;
                return false;
            }

            auto extract = boost::apply_visitor(r::extractor<Iterator>(), parse_result.result);
            if (auto *reply_str = boost::get<r::extracts::string_t>(&extract)) {
                std::cout << "Response: " << reply_str->str << "\n";
            } else {
                std::cout << "Non-string reply received\n";
            }

            rx_buff.consume(parse_result.consumed);
            return true;
        };

        return true;
    }

    #include <boost/asio/unyield.hpp>

private:
    boost::asio::io_service* ios_;
    tcp::socket socket_;
    bredis::Connection<tcp::socket>* connection_;
};

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

int main()
{
    try {
        boost::asio::io_service ios;
        redis_connector rc(ios);

        if (rc.connect("127.0.0.1", "6379")) {
            std::string key = generate_random_binary_string(10);
            std::string value = generate_random_binary_string(20);

            rc.set(key, value);
        }

        ios.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

