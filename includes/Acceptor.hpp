#ifndef _ACCEPTOR_HPP
# define _ACCEPTOR_HPP
# include "Socket.hpp"
# include "Buffer.hpp"
# include <iostream>
namespace ft
{

typedef struct s_config {
	std::string adr;
	int			port;
}t_config;

class Acceptor {
public:
	Acceptor();
	~Acceptor() {};
	Acceptor(t_config conf);
	void HandleConnection();
	class FailAccept : public std::invalid_argument {
	public:
		FailAccept(const std::string& e);
	};
private:
	Socket 		_hostSock;
};

}

#endif