#ifndef SERVER_HPP
# define SERVER_HPP
# include <iostream>
# include "Socket.hpp"
namespace ft
{

class Server {
public:
	Server() {};
	void	addIO(IOService* io) {
		_io = io;
	}
	void	setSocket(Socket* sock) {
		_socket = sock;
	}
	~Server() {};
	int		start(int fd) {
		switch (_io->getCurrentEvent())
		{
		case EVFILT_READ:
			_len = recv(*_socket, buf, 1024, 0);
				std::cerr.write(buf, _len);
				EV_SET(_io->getEventTable(), *_socket, EVFILT_WRITE, EV_ADD | EV_ONESHOT, 0, 0, NULL);
				kevent(_io->getKq(), _io->getEventTable(), 1, NULL, 0, NULL);
			break;
		case EVFILT_WRITE:
			std::cerr << "write\n";
			send(*_socket, buf, _len, 0);
			break;
		default:
			break;
		}
		return 0;
	}
private:
	IOService*	_io;
	Socket*		_socket;
	char		buf[1024];
	int			_len;
};

}

#endif