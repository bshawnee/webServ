# include "../includes/Acceptor.hpp"
# include <map>

ft::Acceptor::Acceptor(ft::t_config conf) : _hostSock(conf.adr, conf.port) {
	int reuse = 1;
	try {
		setsockopt(_hostSock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(int));
		_hostSock.bindHost();
		_hostSock.hostListen(32);
	} catch (std::exception &e) {
		throw ft::Acceptor::FailAccept(std::string(": cant listen"));
	}
}

void 		ft::Acceptor::HandleConnection() {
	struct kevent event;
	struct kevent tEvent[32];
	std::map<int, Buffer> buffered;
	int kq = kqueue();
	if (kq == -1)
		throw ft::Acceptor::FailAccept("Cant init kqueue");
	EV_SET(&event, _hostSock, EVFILT_READ, EV_ADD, 0, 0, NULL);
	kevent(kq, &event, 1, NULL, 0, NULL);
	while (true) {
		int newEvents = kevent(kq, NULL, 0, tEvent, 32, NULL);
		if (newEvents < 0)
			break;
		for (int i = 0; i < newEvents; i++) {
			Socket fd(tEvent[i].ident);
			if (tEvent[i].flags & EV_EOF) {
				buffered.erase(fd);
				std::cerr << "Connection close from remote host\n";
				fd.close();
			} else if (fd == _hostSock) {
				std::cerr << "New connection ";
				Socket* newSock = ft::Socket::acceptConnection(fd);
				buffered[*newSock] = Buffer();
				EV_SET(&event, *newSock, EVFILT_READ, EV_ADD, 0, 0, NULL);
				kevent(kq, &event, 1, NULL, 0, NULL);
				std::cerr << "connection accepted\n";
				delete newSock;
			} else {
				switch (tEvent[i].filter) {
					case EVFILT_READ:
						fd.asyncRead(buffered[fd],
							(t_service){ .event = &event, .kq = kq });
						break;
					case EVFILT_WRITE:
						if (buffered[fd])
							std::cerr << "Can strart response\n";
						fd.asyncWrife(buffered[fd],
							(t_service){ .event = &event, .kq = kq });
						break;
					default:
						std::cerr << "Undefined statement\n";
						break;
				}
			}
		}
	}
}

ft::Acceptor::FailAccept::FailAccept(const std::string &e) : std::invalid_argument(
		e + " \"" + strerror(errno) + "\"") {}