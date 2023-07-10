int main() {
	uWS::App().get("/*", [](auto *res, auto *req) {
		res->end("Hello World!");
	}).listen(9001, [](auto *listenSocket) {
		if (listenSocket) {
			std::cout << "Listening for connections..." << std::endl;
		}
	}).run();

	std::cout << "Shoot! We failed to listen and the App fell through, exiting now!" << std::endl;
}


.get("/hello", [](auto *res, auto *req) {

	/* You can efficiently stream huge files too */
	res->writeHeader("Content-Type", "text/html; charset=utf-8")->end("Hello HTTP!");
	
}).ws<UserData>("/*", {

	/* Just a few of the available handlers */
	.open = [](auto *ws) {
		ws->subscribe("oh_interesting_subject");
	},
	.message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
		ws->send(message, opCode);
	}
	
}).listen(9001, [](auto *listenSocket) {

	if (listenSocket) {
		std::cout << "Listening on port " << 9001 << std::endl;
	} else {
		std::cout << "Failed to load certs or to bind to port" << std::endl;
	}
	
}).run();