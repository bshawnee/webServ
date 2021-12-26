#include "../includes/server/Server.hpp"
# include "../includes/server/Acceptor.hpp"
int		main()
{
	std::string localhost= "127.0.0.1";
	ft::t_adrress host1 = {.port = 30000, .strAdr = &localhost};
	ft::t_adrress host2 = {.port = 30001, .strAdr = &localhost};
	ft::IOService io;
	ft::Acceptor::Hosts v;
	v.push_back(ft::Socket(host1, &io));
	v.push_back(ft::Socket(host2, &io));
	ft::Acceptor acceptor(v, &io);
	while (true)
		acceptor.acceptConnection();
	return 0;
}