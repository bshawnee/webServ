#include "../includes/Acceptor.hpp"
#include <iostream>
int		main() {
	ft::t_config t;
	t.port = 30000;
	t.adr = "127.0.0.1";
	ft::Acceptor acceptor(t);
	try {
		acceptor.HandleConnection();
	} catch (std::exception &e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	return 0;
}