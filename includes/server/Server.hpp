#ifndef SERVER_HPP
# define SERVER_HPP
# include "Socket.hpp"
# include "../handlers/ResponseFactory.h"

namespace ft
{

class Server
{
public:
	Server();
	Server(const Server& ref);
	void	initServer(IOService* io, Socket* sock);
	Server&	operator=(const Server& rhs);
	void	run(ft::IOService::Event& event);
	~Server();

private:
	IOService*	io_;
	Socket*		socket_;
	Buffer		buf_;
};

};

#endif