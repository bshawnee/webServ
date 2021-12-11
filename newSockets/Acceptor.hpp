#ifndef ACCEPTOR_HPP
# define ACCEPTOR_HPP
# include "IOService.hpp"
# include "Server.hpp"
# include <map>
# include <vector>

namespace ft
{

typedef struct s_hostAddress {
	in_addr_t	ipV4;
	int			port;
}				t_HostAdrress;

class Acceptor {
public:
	Acceptor(ft::IOService& service);
	Acceptor(ft::IOService& service, std::vector<t_HostAdrress>& hosts) : _io(service) {
		for (std::vector<t_HostAdrress>::iterator it = hosts.begin();
		it != hosts.end(); it++) {
			try {
				Socket sock(service, it->ipV4, it->port);
			} catch (std::exception& e) {
				e.what();
			}

		}
	};

	void	asyncAccept(/*Server& server*/) {
		//! try
		int	fd = _io.getFdEvent(_sessions);
		if (fd == -1) {
			std::cerr << "Connection close";
			_sessions.erase(_io.getClosedConnection());
			_io.eventOccured();
		} else if (_sessions.find(fd) == _sessions.end() && !_io.getEventTrigger()) {
			Socket sock = ft::Socket(_io, fd);
			_sessions[sock] = ft::Server();
			_sessions[sock].addIO(&_io);
			_sessions[sock].setSocket(&sock);
			EV_SET(_io.getEventTable(), sock, EVFILT_READ, EV_ADD, 0, 0, NULL);
			kevent(_io.getKq(), _io.getEventTable(), 1, NULL, 0, NULL);
			std::cerr << "Connection accepted\n";
		} else if (fd != -1 && !_io.getEventTrigger()) {
			int newFd = _io.getFdEvent(_sessions);
			if (newFd == -1) {
				_sessions.erase(_io.getClosedConnection());
				_io.finishEventSuccsess();
				return ;
			}
			_sessions[newFd].start(fd);
			_io.eventOccured();
		}
		_io.finishEventSuccsess();
	}

private:
	ft::IOService& _io;
	std::map<int, ft::Server> _sessions;
};

}

#endif