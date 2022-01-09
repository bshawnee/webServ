#include "Server_Instance.hpp"

Server::Server(){}

int Server::getSocketFd() const {
	return _socketFd;
}


const sockaddr_in &Server::getSockAddr() const {
	return _sockAddr;
}

void Server::setSockAddr(const sockaddr_in &sockAddr) {
	_sockAddr = sockAddr;
}

const std::string &Server::getHost() const {
	return _host;
}

void Server::setHostAddr(const std::string &host) {
	_host = host;
}

void Server::setPort(const std::string & port) {
	try{
		_port = static_cast<uint16_t>(std::stoi(port));
		if (port.size() != std::to_string(_port).size())
			throw std::exception();
	}
	catch (std::exception &e){
		std::cout << "Port error" << std::endl;
	}
}

void Server::setPort(uint16_t port) {
	_port = port;
}

const std::string &Server::getServName() const {
	return _name;
}

void Server::setServName(const std::string &servName) {
	_name = servName;
}

const std::map<std::string, Location> &Server::getLocation() const {
	return _loc;
}

void Server::setLocation(const std::map<std::string, Location> &location) {
	_loc = location;
}

const std::string &Server::getRoot() const {
	return _root;
}

void Server::setRoot(const std::string &root) {
	_root = root;
}

const std::string Server::getErrorPage() const {
	return _errorPage;
}

void Server::setErrorPage(const std::string  &errorPage) {
	std::string code = errorPage.substr(0, 3);
	std::string file = errorPage.substr(4, errorPage.size() - 4);
	_errorPage = file;
	try {
		_errorCode = std::stoi(code);
	}
	catch (std::exception &e){
		std::cerr << "Error page line error" << std::endl;
	}
}

int Server::createSocket() {
	int listenFd;
	struct sockaddr_in serverAddress;
	if ((listenFd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		std::cerr << "Socket error" << std::endl;
		return -1;
	}
	bzero(&serverAddress, sizeof(serverAddress));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(_host.c_str());
	serverAddress.sin_port = htons(_port);
	int yes = 1;
	if (setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
	{
		std::cerr << "setsockopt error" << std::endl;
		if (close(listenFd) < 0){
            std::cerr << "close error" << std::endl;
		}
		return -2;
	}
	if ((bind(listenFd, (struct sockaddr * )&serverAddress, sizeof serverAddress)) < 0){
		std::cerr << "error bind" << std::endl;
        if (close(listenFd) < 0){
            std::cerr << "close error" << std::endl;
        }
		return -2;
	}
	if (fcntl(listenFd, F_SETFL, O_NONBLOCK) < 0) {
		std::cerr << "error fcntl" << std::endl;
        if (close(listenFd) < 0){
            std::cerr << "close error" << std::endl;
        }
		return -3;
	}
	if (listen(listenFd, 1024) < 0){
		std::cerr << "listen error!" << std::endl;
        if (close(listenFd) < 0){
            std::cerr << "error close" << std::endl;
        }
		return -4;
	}
	_socketFd = listenFd;
	_sockAddr = serverAddress;
	return _socketFd;
}


Server::~Server() {
    if (shutdown(_socketFd, 1) != -1){
        if (close(_socketFd) < 0){
            std::cerr << "error close" << std::endl;
        }
    }
	_loc.clear();
}

uint16_t Server::getPort() const {
	return _port;
}

int Server::getErrorPageCode() const {
	return _errorCode;
}

const std::vector<std::string> &Server::getWhiteList() const {
	return _whiteList;
}

void Server::setWhiteList(const std::string &whiteListPath) {
	std::ifstream file(whiteListPath);
	std::string line;
	if (file.is_open()){
		while (std::getline(file, line))
			_whiteList.push_back(line);

	} else {
		throw std::runtime_error("no whiteList!");
	}
}

const std::string &Server::getAuthBasicUserFile() const {
	return _auth_file;
}

void Server::setAuthBasicUserFile(const std::string &authFile) {
	_auth_file = authFile;
}
