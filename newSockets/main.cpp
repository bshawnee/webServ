#include "Acceptor.hpp"

int		main() {
	ft::t_HostAdrress t1 = {
		.ipV4 = inet_addr("127.0.0.1"),
		.port = 3000
	};
		ft::t_HostAdrress t2 = {
		.ipV4 = inet_addr("127.0.0.1"),
		.port = 3001
	};
	ft::IOService io;
	std::vector<ft::t_HostAdrress> test;
	test.push_back(t1);
	test.push_back(t2);
	ft::Acceptor ac(io, test);
	while (true)
		ac.asyncAccept();
	return 0;
}