#ifndef APP_SERVER_HPP
#define APP_SERVER_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class AppServer {
public:
    AppServer(net::io_context& ioc, tcp::endpoint endpoint);

    // Start the server
    void run();

private:
    void doAccept(net::yield_context yield);

    net::io_context& ioc_;
    tcp::acceptor acceptor_;
};

#endif // APP_SERVER_HPP
