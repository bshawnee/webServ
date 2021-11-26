#ifndef _SOCKET_HPP
# define _SOCKET_HPP
# include <sys/socket.h>
# include <sys/event.h>
# include <arpa/inet.h>
# include <string>
# include <unistd.h>
# include <fcntl.h>
# include "Buffer.hpp"
#include <iostream>
namespace ft {

typedef struct s_service {
	int				kq;
	struct kevent*	event;
}					t_service;

class Socket {
public:
	Socket();
	Socket(int fd);
	Socket(const std::string& adr, int port);
	Socket(const Socket& ref);
	~Socket();

	operator int();
	Socket&			operator=(const Socket& rhs);
	Socket&			operator=(int fd);
	void			bindHost();
	int				getFd() const;
	void			close() const;

	void			asyncRead(ft::Buffer& buf, t_service service) {
		char *tmp = new char[BUFSIZE];
		int n = recv(*this, tmp, BUFSIZE, 0);
		std::cerr << "Bytes readed: " << n << std::endl;
		if (n < 0)
			return ;
		buf.addData(tmp, n);
		if (n < BUFSIZE) {
			EV_SET(service.event, *this, EVFILT_WRITE, EV_ADD | EV_ONESHOT, 0, 0, NULL);
			kevent(service.kq, service.event, 1, NULL, 0, NULL);
		}


	}
	void			asyncWrife(ft::Buffer& buf, t_service service) {
		ft::Buffer::t_buff* chunk = buf.getData();

		int n = send(*this, chunk->chunk, chunk->length, 0);

		if (n < 0)
			return ;
		if (n == BUFSIZE) {
			buf.eraseChunk();
			EV_SET(service.event, *this, EVFILT_WRITE, EV_ADD | EV_ONESHOT, 0, 0, NULL);
			kevent(service.kq, service.event, 1, NULL, 0, NULL);
		} else {
			buf.clearBuffer();
		}
	}
	void			hostListen(unsigned queue);
	static Socket*	acceptConnection(int host);
	class FailOnSocket : public std::exception {
		public:
			virtual const char*	what() const throw();
	};
protected:
	int			_socket;
	sockaddr_in	_info;
};

// bool	operator==(const Socket& lhs, const Socket& rhs);

}

#endif