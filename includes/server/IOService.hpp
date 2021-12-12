#ifndef IOSERVICE_HPP
# define IOSERVICE_HPP
# include <sys/event.h>
# include <exception>
# include <string>
# include <vector>
# include <utility>

# define TRIGGERED_EVENT 32

namespace ft
{
//only one per process


class IOService
{
public:
static const std::string eventMsg[5];
enum EventTrigger
{
	ACCEPT_CONNECTION,
	CLOSE_CONNECTION,
	READ,
	WRITE,
	TIMEOUT
};

	typedef std::pair<int, EventTrigger> Event;
	typedef	struct kevent	event;

	IOService();
	IOService(const IOService& ref);

	~IOService();
	Event		getEvent(std::vector<int>& sockets);
	IOService&	operator=(const IOService& rhs);
	void		addEvent(int socketFd, int event);
	void		incrementEvent();
	class FailOnService : public std::invalid_argument
	{
	public:
		FailOnService(const std::string &errorMsg);
	};
	struct kevent*	getEventTable();
	int				getKq();
private:
	struct kevent*	event_;
	struct kevent*	tEvent_;
	int				kq_;
	int				currentEvent_;
	int				eventsTriggered_;
};

}

#endif