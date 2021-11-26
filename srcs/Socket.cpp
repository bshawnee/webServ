#include "../includes/Socket.hpp"
#include <iostream>
ft::Socket::Socket() : _socket(123) {}
ft::Socket::Socket(int fd) : _socket(fd) {}
ft::Socket::Socket(const Socket& ref) { *this = ref; }
ft::Socket::Socket(const std::string& adr, int port) {
	if ((_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		throw ft::Socket::FailOnSocket();
	_info.sin_addr.s_addr = inet_addr(adr.c_str());
	_info.sin_family = PF_INET;
	_info.sin_len = 0;
	if (_info.sin_addr.s_addr == static_cast<in_addr_t>(-1)) {
		::close(_socket);
		throw ft::Socket::FailOnSocket();
	}
	_info.sin_port = static_cast<in_port_t>(htons(port));
	if (fcntl(_socket, F_SETFL, O_NONBLOCK) < 0) {
		::close(_socket);
		throw ft::Socket::FailOnSocket();
	}
}

ft::Socket::~Socket() {}

void	ft::Socket::close() const {
	::close(_socket);
}

ft::Socket&	ft::Socket::operator=(const Socket& ref) {
	if (this == &ref)
		return *this;
	::close(_socket);
	_socket = ref._socket;
	memcpy(&_info, &ref._info, sizeof(ref._info));
	return *this;
}

ft::Socket&	ft::Socket::operator=(int fd) {
	_socket = fd;
	return *this;
}

ft::Socket*		ft::Socket::acceptConnection(int host) {
	ft::Socket* t = new ft::Socket;
	sockaddr_storage st;
	int flags = fcntl(*t, F_GETFL, 0);
	fcntl(*t, F_SETFL, flags | O_NONBLOCK);
	int len = sizeof(st);

	*t = accept(host, (struct sockaddr*)&st, (socklen_t*)&len);
	if (*t < 0)
		throw ft::Socket::FailOnSocket();
	return t;
}

void		ft::Socket::bindHost() {
	if (bind(_socket, (const sockaddr*)&_info, sizeof(_info)) == -1) {
		throw ft::Socket::FailOnSocket();
	}
}

void		ft::Socket::hostListen(unsigned queue) {
	if (listen(_socket, queue) < 0)
		throw ft::Socket::FailOnSocket();
}


ft::Socket::operator int() { return _socket; }

const char*	ft::Socket::FailOnSocket::what() const throw() {
	return "Broken socket";
}

int		ft::Socket::getFd() const {
	return this->_socket;
}

// bool	ft::operator==(const Socket& lhs, const Socket& rhs) {
// 	return lhs.getFd() == rhs.getFd();
// }