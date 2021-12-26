#ifndef SOCKET_HPP
# define SOCKET_HPP
# include <errno.h>
# include <sys/socket.h>
# include <unistd.h>
# include <fcntl.h>
# include <arpa/inet.h>
# include "IOService.hpp"
# include <iostream>
# include "Buffer.hpp"
# include "../handlers/ResponseFactory.h"

# define	LISTEN_QUEUE	32

namespace ft
{

typedef struct s_adrress
{
	int				port;
	std::string*	strAdr;
}					t_adrress;

enum Error
{
	SUCCESS,
	FAIL_READ,
	FAIL_WRITE,
	REFUSED_CONNECTION,
	HANDLER_ERROR
};


class Socket
{
public:
	Socket();
	Socket(int fd, IOService* io);
	Socket(const t_adrress& adr, IOService* io);
	Socket(const Socket& ref);

	Socket&	operator=(const Socket& ref);
	void	asyncRead(ft::Buffer& buf);
	void	asyncWrite(ft::Buffer& buf);
	void	close() const;
	class FailOnSocket : public std::invalid_argument
	{
	public:
		FailOnSocket(const std::string& errorMsg);
	};
	~Socket();
	operator int();
private:
	struct sockaddr_in	info_;
	int					socketFd_;
	IOService*			service_;
};
a
}

#endif