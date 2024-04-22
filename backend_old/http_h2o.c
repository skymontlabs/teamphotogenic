#include <stdio.h>
#include <stdlib.h>
#include <h2o.h>

static int hello_world(h2o_handler_t *self, h2o_req_t *req) {
    // Create a response
    static h2o_generator_t generator = {NULL, NULL};
    static h2o_iovec_t body = H2O_STRLIT("Hello World!");
    req->res.status = 200;
    req->res.reason = "OK";
    h2o_add_header(&req->pool, &req->res.headers, H2O_TOKEN_CONTENT_TYPE, NULL, H2O_STRLIT("text/plain"));
    h2o_start_response(req, &generator);
    h2o_send(req, &body, 1, H2O_SEND_STATE_FINAL);
    return 0;
}

int main(int argc, char **argv) {
    h2o_globalconf_t config;
    h2o_context_t ctx;
    h2o_accept_ctx_t accept_ctx;
    h2o_hostconf_t *hostconf;
    h2o_handler_t *handler;
    h2o_socket_t *sock;

    // Initialize the library
    h2o_config_init(&config);
    hostconf = h2o_config_register_host(&config, h2o_iovec_init(H2O_STRLIT("default")), 65535);
    handler = h2o_create_handler(hostconf, sizeof(*handler));
    handler->on_req = hello_world;

    // Create the context
    h2o_context_init(&ctx, h2o_evloop_create(), &config);
    accept_ctx.ctx = &ctx;
    accept_ctx.hosts = config.hosts;

    // Bind to port 8080
    sock = h2o_evloop_socket_create(ctx.loop, h2o_socket_bind_address("0.0.0.0", 8080, AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP, 1), H2O_SOCKET_FLAG_DONT_READ);
    if (sock == NULL) {
        fprintf(stderr, "Failed to bind to 0.0.0.0:8080\n");
        return 1;
    }
    h2o_socket_read_start(sock, NULL);
    h2o_accept(&accept_ctx, sock);

    // Enter the event loop
    while (1) {
        h2o_evloop_run(ctx.loop, INT32_MAX);
    }

    // Cleanup (this part of the code is actually never reached in this example)
    h2o_context_dispose(&ctx);
    h2o_config_dispose(&config);

    return 0;
}
