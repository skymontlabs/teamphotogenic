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
std::string generate_random_binary_string(size_t length) {
    std::string str(length, '\0');
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, 255);

    for (auto& c : str) {
        c = static_cast<char>(distribution(generator));
    }

    return str;
}

int main() {
    try {
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query("127.0.0.1", "6379");
        auto iterator = resolver.resolve(query);

        tcp::socket socket(io_service);
        boost::asio::connect(socket, iterator);

        // Create buffers
        bredis::Connection<tcp::socket> c(std::move(socket));
        Buffer rx_buff, tx_buff;

        // Generate random binary strings for key and value
        std::string key = generate_random_binary_string(10); // 10 bytes key
        std::string value = generate_random_binary_string(20); // 20 bytes value

        // Use spawn to run the coroutine
        boost::asio::spawn(io_service,
        [&](boost::asio::yield_context yield) mutable {
            boost::system::error_code error_code;

            // Asynchronously write the command to the server
            auto consumed = c.async_write(tx_buff, bredis::single_command_t("SET", key.data(), value.data()), yield[error_code]);
            tx_buff.consume(consumed);

            if (error_code) {
                std::cerr << "Write error: " << error_code.message() << std::endl;
                return;
            }

            // Asynchronously read the response from the server
            auto parse_result = c.async_read(rx_buff, yield[error_code]);

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

        // Run the io_service to perform the asynchronous operations
        io_service.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

