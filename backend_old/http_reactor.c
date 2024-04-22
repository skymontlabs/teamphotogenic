#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <reactor.h>

void on_request(reactor_event *event)
{
    reactor_http_request *request = (reactor_http_request *) event->data;
    reactor_http_response response;
    char *response_body = "Hello, World!";
    int body_length = strlen(response_body);

    // Prepare the HTTP response
    reactor_http_response_init(&response, 200, "OK", body_length);
    reactor_http_response_header_add(&response, "Content-Type", "text/plain");
    reactor_http_response_body_set(&response, response_body, body_length);

    // Send the response
    reactor_http_respond(event->fd, &response);

    // Close the connection
    reactor_http_close(event->fd);
}

void on_accept(reactor_event *event)
{
    int client_fd = reactor_tcp_accept(event->fd);
    if (client_fd >= 0)
    {
        // Register the client file descriptor for HTTP requests
        reactor_http_open(client_fd, on_request);
    }
}

int main(void)
{
    int server_fd;

    // Initialize the reactor library
    reactor_init();

    // Create a TCP server
    server_fd = reactor_tcp_listen("0.0.0.0", "http", on_accept);
    if (server_fd < 0)
    {
        fprintf(stderr, "Failed to listen on port 80\n");
        exit(EXIT_FAILURE);
    }

    // Run the reactor event loop
    reactor_run();

    // Clean up
    reactor_close(server_fd);
    reactor_finalize();

    return EXIT_SUCCESS;
}
