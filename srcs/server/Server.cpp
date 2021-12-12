#include "../../includes/server/Server.hpp"

static const std::string page = "";

ft::Server::Server() {}

ft::Server::~Server()
{
	// delete socket_;
}

ft::Server::Server(const Server& ref)
{
	*this = ref;
}

void		ft::Server::initServer(ft::IOService* io, ft::Socket* sock)
{
	io_ = io;
	socket_ = sock;
}

void		ft::Server::run(ft::IOService::Event& event)
{
	if (event.second == ft::IOService::READ)
		socket_->asyncRead(buf_);
	if (event.second == ft::IOService::WRITE)
		socket_->asyncWrite(buf_);
}

ft::Server&	ft::Server::operator=(const Server& rhs)
{
	if (this == &rhs)
		return *this;
	io_ = rhs.io_;
	socket_ = rhs.socket_;
	return *this;
}