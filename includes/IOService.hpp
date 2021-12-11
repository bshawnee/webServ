#ifndef IOSERVICE_HPP
# define IOSERVICE_HPP
# include <sys/event.h>
# include <map>
# include "Buffer.hpp"
# define T_EVENT 3

class IOService {
public:
	IOService() {
		_tEvent = new struct kevent [T_EVENT];
		_currentEvent = 0;
		_kq = kqueue();
	};
	~IOService() {
		delete[] _tEvent;
	};
	int		getFdEvent() {
		if (_currentEvent == 0 || _currentEvent >= _newEvents)
			_newEvents = kevent(_kq, NULL, 0, _tEvent, 3, NULL);
		if (_tEvent[_currentEvent].flags & EV_EOF) {
			finishEventSuccsess();
			return -1;
		}
		return _tEvent[_currentEvent].ident;
	}
	int16_t		getCurrentEvent() {
		return _tEvent[_currentEvent].filter;
	}
	void	finishEventSuccsess() {
		++_currentEvent;
	}
private:
	std::map<int, ft::Buffer>	buffer;
	struct kevent*				_tEvent;
	int							_kq;
	int							_currentEvent;
	int							_newEvents;
};

#endif