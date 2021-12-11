#include "../includes/IOService.hpp"

const std::string ft::IOService::eventMsg[5] = {
	"ACCEPT CONNECTION",
	"CLOSE CONNECTION",
	"READ",
	"WRITE",
	"TIMEOUT"
};

ft::IOService::IOService()
{
	eventsTriggered_ = 0;
	tEvent_ = new event [TRIGGERED_EVENT];
	try
	{
		event_ = new event;
	}
	catch (std::exception& e)
	{
		delete [] event_;
		e.what();
	}
	currentEvent_ = 0;
	if ((kq_ = kqueue()) < 0)
	{
		delete [] tEvent_;
		delete event_;
		throw ft::IOService::FailOnService("Cant init kqueue");
	}
}

ft::IOService::~IOService()
{
	delete [] tEvent_;
	delete event_;
}

ft::IOService::IOService(const ft::IOService& ref)
{
	*this = ref;
}

void			ft::IOService::addEvent(int socketFd, int event)
{
	if (EVFILT_READ == event)
	{
		EV_SET(event_, socketFd, EVFILT_READ, EV_ADD, 0, 0, NULL);
		if (kevent(kq_, event_, 1, NULL, 0, NULL) < 0)
			throw ft::IOService::FailOnService("Cant add event read");
	}
	else if (EVFILT_WRITE == event)
	{
		EV_SET(event_, socketFd, EVFILT_WRITE, EV_ADD | EV_ONESHOT, 0, 0, NULL);
		if (kevent(kq_, event_, 1, NULL, 0, NULL))
			throw ft::IOService::FailOnService("Cant add event write");
	}
	else
		throw ft::IOService::FailOnService("Unsupported event");
}

ft::IOService::Event		ft::IOService::getEvent(std::vector<int>& sockets)
{
	if (currentEvent_ == 0 || currentEvent_ == eventsTriggered_)
	{
		currentEvent_ = 0;
		eventsTriggered_ = kevent(kq_, NULL, 0, tEvent_,TRIGGERED_EVENT, NULL);
		if (eventsTriggered_ < 0)
			throw ft::IOService::FailOnService("Fail on eventloop or timeout");
	}
	if (tEvent_[currentEvent_].flags & EV_EOF)
		return std::pair<int, ft::IOService::EventTrigger>(tEvent_[currentEvent_].ident, CLOSE_CONNECTION);
	for (std::vector<int>::iterator hostSocket = sockets.begin(); hostSocket != sockets.end(); hostSocket++)
	{
		if (tEvent_[currentEvent_].ident == *hostSocket)
			return std::pair<int, ft::IOService::EventTrigger>(*hostSocket, ACCEPT_CONNECTION);
	}
	if (tEvent_[currentEvent_].filter == EVFILT_READ)
		return std::pair<int, ft::IOService::EventTrigger>(tEvent_[currentEvent_].ident, READ);
	if (tEvent_[currentEvent_].filter == EVFILT_WRITE)
		return std::pair<int, ft::IOService::EventTrigger>(tEvent_[currentEvent_].ident, WRITE);
	return ft::IOService::Event(-1, TIMEOUT);
}

void			ft::IOService::incrementEvent()
{
	++currentEvent_;
}

struct kevent*	ft::IOService::getEventTable()
{
	return event_;
}

int				ft::IOService::getKq()
{
	return kq_;
}

ft::IOService&	ft::IOService::operator=(const ft::IOService& rhs)
{
	if (this == &rhs)
		return *this;
	delete this->event_;
	delete [] this->tEvent_;
	this->event_ = rhs.event_;
	this->tEvent_ = rhs.tEvent_;
	this->kq_ = rhs.kq_;
	this->currentEvent_ = rhs.currentEvent_;
	this->eventsTriggered_ = rhs.eventsTriggered_;
	return *this;
}

ft::IOService::FailOnService::FailOnService(const std::string& errorMsg) :
	std::invalid_argument(errorMsg + ": \"" + strerror(errno) + "\"") {}