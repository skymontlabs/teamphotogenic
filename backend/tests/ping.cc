#include <boost/asio.hpp>
#include <bredis/Connection.hpp>
#include <bredis/Extract.hpp>
#include <iostream>

using boost::asio::ip::tcp;
namespace r = bredis;

#include <boost/asio/yield.hpp>

class RedisPingOperation : public boost::asio::coroutine
{
    tcp::socket socket_;
    r::Connection<tcp::socket> redis_connection_;
    r::markers::redis_result_t result_;

public:
    RedisPingOperation(boost::asio::io_context& io_context, const tcp::endpoint& endpoint)
        : socket_(io_context), redis_connection_(std::move(socket_)) {
        socket_.connect(endpoint);
    }

    void operator()(boost::system::error_code ec = {}) {
        if (ec) {
            std::cerr << "Error: " << ec.message() << std::endl;
            return;
        }

        reenter (this) {
            yield redis_connection_.async_write(bredis::single_command_t("PING"),
            [this]() {

            });

            yield redis_connection_.async_read(std::move(*this),
            [this]() {

            });

            result_ = boost::apply_visitor(r::extractor<tcp::socket>(), redis_connection_.reply());

            if (auto *reply = boost::get<r::positive_parse_result_t>(&result_)) {
                std::string pong = boost::apply_visitor(r::extractor<tcp::socket>(), reply->result);
                std::cout << "Received: " << pong << std::endl;
            } else {
                std::cerr << "Failed to receive PONG" << std::endl;
            }
        }
    }
};

#include <boost/asio/unyield.hpp>

int main() {
    try {
        boost::asio::io_context io_context;
        tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 6379);

        RedisPingOperation ping_operation(io_context, endpoint);
        ping_operation();

        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}