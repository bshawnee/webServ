#include "../../includes/server/Acceptor.hpp"

ft::Acceptor::Acceptor() {}

ft::Acceptor::Acceptor(const ft::Acceptor::Hosts& hosts, ft::IOService* io) :
io_(io), hosts_(hosts) {}

ft::Acceptor::Acceptor(const ft::Acceptor& ref)
{
	*this = ref;
}

ft::Acceptor::~Acceptor() {}

void			ft::Acceptor::acceptConnection()
{
	std::vector<int> hostsIo(hosts_.begin(), hosts_.end());
	ft::IOService::Event eventTrigger = io_->getEvent(hostsIo);
	std::cerr << ft::IOService::eventMsg[static_cast<int>(eventTrigger.second)] << std::endl;
	if (eventTrigger.second == ft::IOService::CLOSE_CONNECTION)
	{
		std::cerr << "Connection closed\n";
		::close(eventTrigger.first);
		servers_.erase(eventTrigger.first);
	}
	else if (eventTrigger.second == ft::IOService::ACCEPT_CONNECTION)
	{
		ft::Socket* tmp = new ft::Socket(eventTrigger.first, io_);
		std::cerr << "Accepted new connection on " << *tmp << std::endl;
		io_->addEvent(*tmp, EVFILT_READ);
		servers_[*tmp] = ft::Server();
		servers_[*tmp].initServer(io_, tmp);
	}
	else if (eventTrigger.second == ft::IOService::READ ||
			 eventTrigger.second == ft::IOService::WRITE)
	{
		if (servers_.find(eventTrigger.first) != servers_.end())
			servers_[eventTrigger.first].run(eventTrigger);
		else
			std::cerr << "Critical ERROR\n";
	}
	io_->incrementEvent();
}

ft::Acceptor&	ft::Acceptor::operator=(const ft::Acceptor& rhs)
{
	if (this == &rhs)
		return *this;
	io_ = rhs.io_;
	hosts_ = rhs.hosts_;
	servers_ = rhs.servers_;
	return *this;
}