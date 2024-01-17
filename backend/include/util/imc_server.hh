#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <array>

using boost::asio::ip::tcp;

class imc_session : public boost::asio::coroutine, public std::enable_shared_from_this<imc_session> {
public:
    imc_session(tcp::socket socket) : socket_(std::move(socket)) {}

    void start() { (*this)(); }

private:
    void operator()(boost::system::error_code ec = {}, std::size_t length = 0) {
        if (!ec) reenter(this) {
            while (true) {
                yield socket_.async_read_some(boost::asio::buffer(data_),
                    [self = shared_from_this()](boost::system::error_code ec, std::size_t length) {
                        (*self)(ec, length);
                    });

                yield boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
                    [self = shared_from_this()](boost::system::error_code ec, std::size_t length) {
                        (*self)(ec, length);
                    });
            }
        }
    }

    tcp::socket socket_;
    std::array<char, 1024> data_;
};

class imc_server {
public:
    imc_server(boost::asio::io_context& io_context, short port)
        : io_context_(io_context), acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        start_accept();
    }

private:
    void start_accept() {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket) {
                if (!ec) {
                    std::make_shared<imc_session>(std::move(socket))->start();
                }

                start_accept();
            });
    }

    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;
};

int main() {
    try {
        boost::asio::io_context io_context;
        imc_server s(io_context, 1234);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
