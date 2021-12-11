#include "../includes/Socket.hpp"

ft::Socket::Socket() : socketFd_(0), service_(NULL) {}

ft::Socket::Socket(const ft::Socket& ref)
{
	*this = ref;
}

ft::Socket::Socket(int fd, IOService* io) : service_(io)
{
	sockaddr_storage info;
	if (fd < 0)
		throw ft::Socket::FailOnSocket("Cant create new socket");
	int flags;
	flags = fcntl(fd, F_GETFL, 0);
	if (flags < 0)
		throw ft::Socket::FailOnSocket("Failure on get flags socket");
	if (fcntl(fd, F_SETFL, 0) < 0)
		throw ft::Socket::FailOnSocket("Cant set connection to noneblock state");
	if ((socketFd_ = accept(fd, reinterpret_cast<struct sockaddr*>(&info), (socklen_t*)&info)) < 0)
		throw ft::Socket::FailOnSocket("Cant accept new connection");
	io->addEvent(fd, EVFILT_READ);
}

ft::Socket::~Socket() {}

ft::Socket::FailOnSocket::FailOnSocket(const std::string& errorMsg) :
	std::invalid_argument(errorMsg + ": \"" + strerror(errno) + "\"") {}

ft::Socket::Socket(const t_adrress& adr, ft::IOService* io) : service_(io)
{
	this->socketFd_ = socket(PF_INET, SOCK_STREAM, 0);
	if (this->socketFd_ < 0)
		throw ft::Socket::FailOnSocket("Can't open socket");
	if ((this->info_.sin_addr.s_addr = inet_addr(adr.strAdr->c_str())) < 0)
	{
		::close(socketFd_);
		throw ft::Socket::FailOnSocket("Incorrect ipV4 adrress");
	}
	info_.sin_family = PF_INET;
	info_.sin_len = 0;
	info_.sin_port = htons(adr.port);
	if (fcntl(socketFd_, F_SETFL, O_NONBLOCK) < 0)
	{
		::close(socketFd_);
		throw ft::Socket::FailOnSocket("Cant set socket to noneblock state");
	}
	if (bind(socketFd_, reinterpret_cast<const sockaddr*>(&info_), sizeof(info_)) < 0)
	{
		::close(socketFd_);
		throw ft::Socket::FailOnSocket("Cant bind Socket");
	}
	if (listen(socketFd_, LISTEN_QUEUE) < 0)
	{
		::close(socketFd_);
		throw ft::Socket::FailOnSocket("Cant listen port");
	}
	io->addEvent(socketFd_, EVFILT_READ);
}

ft::Socket::operator int()
{
	return socketFd_;
}

void		ft::Socket::asyncRead(ft::Buffer& buf)
{
	char* tmp = new char [BUFSIZE];
	int n = recv(*this, tmp, BUFSIZE, 0);
	// ! if (n < 0)
	// ! return event::Error;
	buf.addData(tmp, n);
	if (n < BUFSIZE)
	{
		EV_SET(service_->getEventTable(), *this, EVFILT_WRITE, EV_ADD | EV_ONESHOT, 0, 0, NULL);
		kevent(service_->getKq(), service_->getEventTable(), 1, NULL, 0, NULL);
	}
}

void		ft::Socket::asyncWrite(ft::Buffer& buf)
{
	ft::Buffer::t_buff* chunk = buf.getData();
	int n = send(*this, chunk->chunk, chunk->length, 0);
	// !if (n < 0)
	//!	return event::ERROR;
	if (n == BUFSIZE)
	{
		buf.eraseChunk();
		EV_SET(service_->getEventTable(), *this, EVFILT_WRITE, EV_ADD | EV_ONESHOT, 0, 0, NULL);
		kevent(service_->getKq(), service_->getEventTable(), 1, NULL, 0, NULL);
	}
	else
	{
		buf.clearBuffer();
	}
}

ft::Socket&	ft::Socket::operator=(const ft::Socket& ref)
{
	if (this == &ref)
		return *this;
	this->socketFd_ = ref.socketFd_;
	this->service_ = ref.service_;
	return *this;
}

void		ft::Socket::close() const
{
	::close(socketFd_);
}



