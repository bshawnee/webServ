#ifndef ACCEPTOR_HPP
# define ACCEPTOR_HPP
# include "Server.hpp"
# include <map>

namespace ft
{


class Acceptor
{
public:
	typedef std::vector<ft::Socket> Hosts;
	Acceptor();
	Acceptor(const Hosts& hosts, IOService* io);
	Acceptor(const Acceptor& ref);

	~Acceptor();
	void		acceptConnection();
	Acceptor&	operator=(const Acceptor& rhs);
private:
	IOService*	io_;
	Hosts		hosts_;
	std::map<int, Server> servers_;
	//TODO HANDLERS READ_WRITE
};

};

#endif