#ifndef IOSERVICE_HPP
# define IOSERVICE_HPP
# include <sys/event.h>
# include <exception>
# include <map>
# include <iostream>
#include <unistd.h>
# define T_EVENT			32
# define EVENT_CLOSE		0
# define EVENT_NEW_CONNECT	1
# define EVENT_READ			2
# define EVENT_WRITE		3
# define EVENT_NONE			-1

namespace ft
{

class Server;

class IOService {
public:
	IOService() {
		_tEvent = new struct kevent [3];
		_currentEvent = 0;
		_eventTriggered = false;
		_event = new struct kevent;
		_kq = kqueue();
	};
	~IOService() {
		delete[] _tEvent;
	};
	int		getFdEvent(std::map<int, ft::Server>& servers) {
		if (_currentEvent == 0 || _currentEvent == _newEvents) {
			_currentEvent = 0;
			_newEvents = kevent(_kq, NULL, 0, _tEvent, T_EVENT, NULL);
			_eventTriggered = false;
			//! if (_newEvents < 0)
			//! 	throw
			// std::cerr << _newEvents << std::endl;
		}
		if (_tEvent[_currentEvent].flags & EV_EOF) {
			_trigger = EVENT_CLOSE;
			_closedFd = _tEvent[_currentEvent].ident;
			std::cerr << "Close connection";
			::close(_tEvent[_currentEvent].ident);
			return -1;
		}
		else if (servers.find(_tEvent[_currentEvent].ident) == servers.end())
			_trigger = EVENT_NEW_CONNECT;
		else {
			if (_tEvent[_currentEvent].filter == EVFILT_READ)
				_trigger = EVENT_READ;
			else if (_tEvent[_currentEvent].filter == EVENT_WRITE)
				_trigger = EVENT_WRITE;
		}
		return _tEvent[_currentEvent].ident;
	}
	int			getTrigger() const {
		return _trigger;
	}
	void		eventOccured() {
		_eventTriggered = true;
	}
	bool		getEventTrigger() const {
		return _eventTriggered;
	}
	int			getClosedConnection() const {
		return _closedFd;
	}
	int			getKq() const {
		return _kq;
	}
	struct kevent*	getEventTable() {
		return _event;
	}
	int16_t		getCurrentEvent() const {
		return _tEvent[_currentEvent].filter;
	}
	void	finishEventSuccsess() {
		_currentEvent += 1;
	}
private:
	int				_trigger;
	int				_closedFd;
	struct kevent*	_event;
	struct kevent*	_tEvent;
	bool			_eventTriggered;
	int				_kq;
	int				_currentEvent;
	int				_newEvents;
};

}

#endif