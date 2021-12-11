#ifndef SOCKET_HPP
# define SOCKET_HPP
# include <sys/socket.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <unistd.h>
# include "IOService.hpp"
# define QUEUE 32

namespace ft
{

class IOService;

class Socket {
public:
	Socket(ft::IOService& service, in_addr_t ipV4, int port) : _io(service) {
	if ((_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		throw ft::Socket::FailOnSocket("Cant open socket");
	_info.sin_addr.s_addr = ipV4;
	_info.sin_family = PF_INET;
	_info.sin_len = 0;
	if (_info.sin_addr.s_addr == static_cast<in_addr_t>(-1)) {
		::close(_socket);
		throw ft::Socket::FailOnSocket("Incorrect ip address");
	}
	_info.sin_port = static_cast<in_port_t>(htons(port));
	if (fcntl(_socket, F_SETFL, O_NONBLOCK) < 0) {
		::close(_socket);
		throw ft::Socket::FailOnSocket("Cant set socket to noneblock state");
	}
	if (bind(_socket, (const sockaddr*)&_info, sizeof(_info)) == -1)
		throw ft::Socket::FailOnSocket("Cant bind socket");
	if (listen(_socket, QUEUE) < 0)
		throw ft::Socket::FailOnSocket("Cant listen");
	EV_SET(_io.getEventTable(), _socket, EVFILT_READ, EV_ADD, 0, 0, NULL);
	kevent(_io.getKq(), _io.getEventTable(), 1, NULL, 0, NULL);
	}

	Socket(ft::IOService& service, int fd) : _io(service) {
		sockaddr_storage st;
		int flags = fcntl(fd, F_GETFL, 0);
		if (flags < 0)
			throw ft::Socket::FailOnSocket("Fcntl fail\n");
		if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0)
			throw ft::Socket::FailOnSocket("Fcntl fail, NONEBLOCK");
		int len = sizeof(st);
		_socket = accept(fd, (struct sockaddr*)&st, (socklen_t*)&len);
		if (_socket < 0)
			ft::Socket::FailOnSocket("Cant accept");
	}

	class FailOnSocket : public std::invalid_argument {
	public:
		FailOnSocket(const std::string &e) : std::invalid_argument(e) {}
	};
	operator int() {
		return _socket;
	}
private:
	int			_socket;
	struct sockaddr_in _info;
	IOService&	_io;
};

}

#endif