//------------------------------------------------------------------------------
//
// Example: WebSocket server, stackless coroutine
//
//------------------------------------------------------------------------------

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
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
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

using sess2user = std::unordered_map<session*, userdata>;
using user2sess = std::unordered_map<userdata, session*>;

//------------------------------------------------------------------------------

// Report a failure
void fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}


// Adjust settings on the stream
template<class NextLayer>
void setup_stream(websocket::stream<NextLayer>& ws)
{
    // These values are tuned for Autobahn|Testsuite, and
    // should also be generally helpful for increased performance.

    websocket::permessage_deflate pmd;
    pmd.client_enable = false;
    pmd.server_enable = false;
    //pmd.compLevel = 3;
    ws.set_option(pmd);

    // Fragment will slow it down
    ws.auto_fragment(false);

    // Large size
    ws.read_message_max(256 * 1024 * 1024);
}



// Echoes back all received WebSocket messages
class session: public boost::asio::coroutine
//, public std::enable_shared_from_this<session>
{
    websocket::stream<beast::tcp_stream> ws_;
    beast::flat_buffer buffer_;

    sess2user& s2u_;
    user2sess& u2s_;

public:
    // Take ownership of the socket
    explicit session(tcp::socket socket, sess2user& session_list):
    ws_(std::move(socket)),
    all_sessions_(session_list)
    {
        setup_stream(ws_);
    }

    // Start the asynchronous operation
    void run()
    {
        // We need to be executing within a strand to perform async operations
        // on the I/O objects in this session. Although not strictly necessary
        // for single-threaded contexts, this example code is written to be
        // thread-safe by default.

        net::dispatch(ws_.get_executor(),
        [this](beast::error_code ec, std::size_t bytes_transferred) {
            this->loop(ec, bytes_transferred);
        });
    }

    #include <boost/asio/yield.hpp>

    void loop(beast::error_code ec, std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);
        reenter(*this) {
            ws_.set_option(websocket::stream_base::timeout::suggested(beast::role_type::server));

            /*
            ws_.set_option(websocket::stream_base::decorator(
            [](websocket::response_type& res) {
                res.set(http::field::server, "websocket-server-stackless");
            }));*/

            // import new sessions
            auto it = all_sessions_.find(this);
            if (it == all_sessions_.end()) {
                all_sessions_.insert(this);
            } else {


            }


            rlim_.grant_access();


            yield ws_.async_accept(
            [this](beast::error_code ec) {
                this->loop(ec, 0);
            });

            if (ec) return fail(ec, "accept");

            for (;;) {
                yield ws_.async_read(buffer_,
                [this](beast::error_code ec, std::size_t bytes_transferred) {
                    this->loop(ec, bytes_transferred);
                });

                if (ec == websocket::error::closed) return;
                if (ec) fail(ec, "read");

                // gateway
                gwy_.handle_req();


                ws_.text(false);
                
                yield ws_.async_write(buffer_.data(),
                [this](beast::error_code ec, std::size_t bytes_transferred) {
                    this->loop(ec, bytes_transferred);
                });

                if (ec) return fail(ec, "write");
                buffer_.consume(buffer_.size());
            }
        }
    }

    #include <boost/asio/unyield.hpp>
};

//------------------------------------------------------------------------------

// Accepts incoming connections and launches the sessions
class listener: public boost::asio::coroutine //, public std::enable_shared_from_this<listener>
{
    net::io_context& ioc_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;

    session_map all_sessions_;

public:
    listener(net::io_context& ioc, tcp::endpoint endpoint):
    ioc_(ioc),
    acceptor_(net::make_strand(ioc)),
    socket_(net::make_strand(ioc))
    {
        beast::error_code ec;

        // Open the acceptor
        acceptor_.open(endpoint.protocol(), ec);
        if (ec) {
            fail(ec, "open");
            return;
        }

        // Allow address reuse
        acceptor_.set_option(net::socket_base::reuse_address(true), ec);
        if (ec) {
            fail(ec, "set_option");
            return;
        }

        // Bind to the server address
        acceptor_.bind(endpoint, ec);
        if (ec) {
            fail(ec, "bind");
            return;
        }

        // Start listening for connections
        acceptor_.listen(net::socket_base::max_listen_connections, ec);
        if (ec) {
            fail(ec, "listen");
            return;
        }
    }

    // Start accepting incoming connections
    void run()
    {
        loop();
    }

private:

    #include <boost/asio/yield.hpp>


    void loop(beast::error_code ec = {})
    {
        reenter(*this) {
            for (;;) {
                yield acceptor_.async_accept(socket_, [this](beast::error_code ec) {
                    this->loop(ec);
                });

                if (ec) {
                    fail(ec, "accept");
                } else {
                    // Allocate memory for the session manually
                    void* raw_memory = std::malloc(sizeof(session));
                    if (raw_memory) {
                        // Construct a session using placement new
                        session* new_session = new(raw_memory) session(std::move(socket_));

                        // Start the session
                        new_session->run();

                        // You must ensure to call delete on new_session somewhere in your code
                        // after the session has ended, followed by std::free on raw_memory

                    } else {
                        // Handle allocation failure
                        throw "error with allocating new session";
                        break; // Or however you wish to handle the error
                    }
                }

                // Make sure each session gets its own strand
                socket_ = tcp::socket(net::make_strand(ioc_));
            }
        }
    }



    #include <boost/asio/unyield.hpp>
};

/*
                    session* ssn = spool.alloc();

                    // Use placement new to construct the 'session' object in the allocated memory
                    session* my_session = new(ssn) session(std::move(socket_));

                    ssn->run();*/
//------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    // Check command line arguments.
    if (argc != 4)
    {
        std::cerr <<
            "Usage: websocket-server-stackless <address> <port> <threads>\n" <<
            "Example:\n" <<
            "    websocket-server-stackless 0.0.0.0 8080 1\n";
        return EXIT_FAILURE;
    }
    auto const address = net::ip::make_address(argv[1]);
    auto const port = static_cast<unsigned short>(std::atoi(argv[2]));
    auto const threads = std::max<int>(1, std::atoi(argv[3]));

    // The io_context is required for all I/O
    net::io_context ioc{threads};

    // Create and launch a listening port
    listener*lis = new listener(ioc, tcp::endpoint{address, port});
    lis->run();

    // Run the I/O service on the requested number of threads
    std::vector<std::thread> v;
    v.reserve(threads - 1);
    for(auto i = threads - 1; i > 0; --i)
        v.emplace_back(
        [&ioc]
        {
            ioc.run();
        });
    ioc.run();

    free(lis);

    return EXIT_SUCCESS;
}
