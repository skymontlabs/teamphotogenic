#include "example/common/server_certificate.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/dispatch.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//------------------------------------------------------------------------------

// Report a failure
void
fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

// Echoes back all received WebSocket messages
ws_session::ws_session(tcp::socket&& socket, ssl::context& ctx):
ws_(std::move(socket), ctx) {}

// Start the asynchronous operation
void ws_session::run()
{
    // We need to be executing within a strand to perform async operations
    // on the I/O objects in this ws_session. Although not strictly necessary
    // for single-threaded contexts, this example code is written to be
    // thread-safe by default.
    net::dispatch(ws_.get_executor(),
                  beast::bind_front_handler(&ws_session::loop,
                                            shared_from_this(),
                                            beast::error_code{},
                                            0));
}

#include <boost/asio/yield.hpp>

void ws_session::loop(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    reenter(*this)
    {
        // Set the timeout.
        beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(30));

        // Perform the SSL handshake
        yield ws_.next_layer().async_handshake(
            ssl::stream_base::server,
            std::bind(
                &ws_session::loop,
                shared_from_this(),
                std::placeholders::_1,
                0));
        if(ec)
            return fail(ec, "handshake");

        // Turn off the timeout on the tcp_stream, because
        // the websocket stream has its own timeout system.
        beast::get_lowest_layer(ws_).expires_never();

        // Set suggested timeout settings for the websocket
        ws_.set_option(
            websocket::stream_base::timeout::suggested(
                beast::role_type::server));

        // Set a decorator to change the Server of the handshake
        ws_.set_option(websocket::stream_base::decorator(
            [](websocket::response_type& res)
            {
                res.set(http::field::server,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-server-stackless-ssl");
            }));

        // Accept the websocket handshake
        yield ws_.async_accept(
            std::bind(
                &ws_session::loop,
                shared_from_this(),
                std::placeholders::_1,
                0));
        if(ec)
            return fail(ec, "accept");

        for(;;)
        {
            // Read a message into our buffer
            yield ws_.async_read(
                buffer_,
                std::bind(
                    &ws_session::loop,
                    shared_from_this(),
                    std::placeholders::_1,
                    std::placeholders::_2));
            if(ec == websocket::error::closed)
            {
                // This indicates that the ws_session was closed
                return;
            }
            if(ec)
                fail(ec, "read");

            // Echo the message
            ws_.text(ws_.got_text());
            yield ws_.async_write(
                buffer_.data(),
                std::bind(
                    &ws_session::loop,
                    shared_from_this(),
                    std::placeholders::_1,
                    std::placeholders::_2));
            if(ec)
                return fail(ec, "write");

            // Clear the buffer
            buffer_.consume(buffer_.size());
        }
    }
}

#include <boost/asio/unyield.hpp>
