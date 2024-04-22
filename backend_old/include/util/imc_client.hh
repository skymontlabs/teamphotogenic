#include <boost/asio.hpp>
#include <iostream>
#include <array>
#include <memory>
#include <string>
#include <thread>

using boost::asio::ip::tcp;

class chat_client : public boost::asio::coroutine, public std::enable_shared_from_this<chat_client> {
public:
    chat_client(boost::asio::io_context& io_context, const tcp::resolver::results_type& endpoints)
        : io_context_(io_context), socket_(io_context), endpoints_(endpoints) {}

    void start() {
        boost::asio::async_connect(socket_, endpoints_,
            [self = shared_from_this()](boost::system::error_code ec, const tcp::endpoint&) {
                self->on_connect(ec);
            });
    }

    void write(const std::string& message) {
        io_context_.post(
            [self = shared_from_this(), message]() {
                bool write_in_progress = !self->write_msgs_.empty();
                self->write_msgs_.push_back(message);
                if (!write_in_progress) {
                    self->do_write();
                }
            });
    }

    void close() {
        io_context_.post([self = shared_from_this()]() { self->do_close(); });
    }

private:
    void on_connect(const boost::system::error_code& ec) {
        if (!ec) {
            (*this)();
        } else {
            std::cerr << "Failed to connect: " << ec.message() << std::endl;
        }
    }

    void operator()(boost::system::error_code ec = {}, std::size_t length = 0) {
        if (!ec) reenter (this) {
            while (socket_.is_open()) {
                yield boost::asio::async_read_until(socket_, boost::asio::dynamic_buffer(read_msg_), "\n",
                    [self = shared_from_this()](boost::system::error_code ec, std::size_t length) {
                        self->on_read(ec, length);
                    });
            }
        }
    }

    void do_write() {
        auto& message = write_msgs_.front();
        boost::asio::async_write(socket_, boost::asio::buffer(message),
            [self = shared_from_this()](boost::system::error_code ec, std::size_t /*length*/) {
                self->on_write(ec);
            });
    }

    void on_read(const boost::system::error_code& ec, std::size_t /*length*/) {
        if (!ec) {
            std::cout << "Server: " << read_msg_ << std::endl;
            read_msg_.clear();
            (*this)();
        } else {
            do_close();
        }
    }

    void on_write(const boost::system::error_code& ec) {
        if (!ec) {
            write_msgs_.pop_front();
            if (!write_msgs_.empty()) {
                do_write();
            }
        } else {
            do_close();
        }
    }

    void do_close() {
        socket_.close();
    }

    boost::asio::io_context& io_context_;
    tcp::socket socket_;
    tcp::resolver::results_type endpoints_;
    std::string read_msg_;
    std::deque<std::string> write_msgs_;
};

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: chat_client <host> <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(argv[1], argv[2]);

        auto client = std::make_shared<chat_client>(io_context, endpoints);
        client->start();

        std::thread t([&io_context]() { io_context.run(); });

        std::string line;
        while (std::getline(std::cin, line)) {
            client->write(line + "\n");
        }

        client->close();
        t.join();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
