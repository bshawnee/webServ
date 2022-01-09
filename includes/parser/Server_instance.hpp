#ifndef SERVER_INSTANCE_HPP 
#define SERVER_INSTANCE_HPP

# include <string>
# include <iostream>
# include <istream>
# include <map>
# include "Location.hpp"
# include <arpa/inet.h>
# include <netdb.h>
# include <unistd.h>
# include <vector>
# include <fcntl.h>
# include <string.h>
# include <fstream>



class Server {
private:
	int									_socketFd;
	struct sockaddr_in					_sockAddr;

	std::string							_host;
	uint16_t							_port;
	std::string							_name;
	std::map<std::string, Location>		_loc;
	std::string							_root;
	std::string							_errorPage;
	int 								_errorCode;
	std::vector<std::string>			_whiteList;
	std::string							_auth_file;

	Server(const Server &other);
	Server &operator=(const Server &other);

public:
	Server();
	virtual ~Server();

	void									setHostAddr(const std::string &host);
	void									setSockAddr(const sockaddr_in &socketAddr);
	void									setServName(const std::string &serverName);
	void									setLocation(const std::map<std::string, Location> &location);
	void									setRoot(const std::string &root);
	void									setErrorPage(const std::string &errorPage);
	void									setFds(const std::vector<int> &fds);
	void									setPort(const std::string & port);
	void									setPort(uint16_t port);
	void									setWhiteList(const std::string &whiteListPath);
	void									setAuthBasicUserFile(const std::string &authBasicUserFile);

	int										getSocketFd() const;
	const sockaddr_in						&getSockAddr() const;
	const std::string						&getHost() const;
	uint16_t 								getPort() const;
	const std::string						&getServName() const;
	const std::map<std::string, Location>	&getLocation() const;
	const std::string						&getRoot() const;
	const std::string						getErrorPage() const;
	const std::vector<int>					&getFds() const;
	const std::vector<std::string>			&getWhiteList() const;
	const std::string						&getAuthBasicUserFile() const;
	int										getErrorPageCode() const;

	int createSocket();
	void print();
};


#endif
