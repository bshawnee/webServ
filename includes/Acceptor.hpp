#ifndef _ACCEPTOR_HPP
# define _ACCEPTOR_HPP
# include "Socket.hpp"
# include "Buffer.hpp"
# include <iostream>
# include "HttpRequest.hpp"

namespace ft
{

typedef struct s_config {
	std::string adr;
	int			port;
}t_config;

typedef struct s_ioService {
	struct kevent	event;
	struct kevent	*tEvent;
	int				kq;
}					t_ioService;;

class Acceptor {
public:
	Acceptor(t_ioService* io);
	~Acceptor() {};
	Acceptor(t_config conf);
	void HandleConnection();
	class FailAccept : public std::invalid_argument {
	public:
		FailAccept(const std::string& e);
	};
private:
	Socket 		_hostSock;
	HttpRequest	_request;
};

}

#endif