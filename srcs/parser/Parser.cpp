#include "Parser.hpp"

Parser::~Parser() {}

Parser::Parser(const Parser &other) {
	(void)other;
}

Parser &Parser::operator=(const Parser &other) {
	(void)other;
	return *this;
}

Parser::Parser(const std::string &name) {
	std::ifstream f(name);
	if (!f.is_open()) {
		throw std::runtime_error("error: file");
	}

	parseConfig(f);
	validateConfig();
	f.close();
}

void Parser::validateConfig(void) {
	for (int i = 0; i < _servers.size(); i++) {
		try {
			if (!_servers[i]->getAuthBasicUserFile().empty())
				_servers[i]->setWhiteList(_servers[i]->getAuthBasicUserFile());
		} catch (std::exception &exception) {
			throw std::runtime_error(exception.what());
		}
	}
	for (int i = 0; i < _servers.size(); i++){
	    for (size_t j = i + 1; j < _servers.size(); ++j){
	        if (_servers[i]->getPort() == _servers[j]->getPort())
                throw std::runtime_error("Port error");
	    }
	}

	for (int i = 0; i < _servers.size(); i++) {
		if (_servers[i]->getServName().empty())
			throw std::runtime_error("servers name not found");
		if (_servers[i]->getPort() < 1024 || _servers[i]->getPort() > 65535)
			throw std::runtime_error("ports diapazon error");
		if (_servers[i]->getLocation().empty())
			throw std::runtime_error("location error");
	}
}

const std::vector<Server *> &Parser::getServers() const {
	return _servers;
}

void Parser::parseConfig(std::ifstream &fd) {
	std::string buffer;
	std::vector<std::string> conf;

	size_t i = 0;
	while (std::getline(fd, buffer)) {
		if (buffer == "server:") {
			if (conf.size() != 0) {
				getServer(conf, i);
				i++;
				conf.clear();
			}
		} else if ((buffer.find("server:") != std::string::npos && (buffer.compare(0, 7, "server:")) && buffer.size() != 7)) {
			throw std::runtime_error("config: server line error");
		}
		conf.push_back(buffer);
	}
	if (conf[0] == "server:") {
		getServer(conf, i);
	}
	if (conf.size() == 0)
		throw std::runtime_error("config: server line error");
}

std::string parseLine(std::string com, std::string &str, size_t tab) {
	std::string temp;
	size_t i = 0;
	while (str[i] == '\t') {
		i++;
	}
	if (i != tab) {
		throw std::runtime_error("Tabulation error");
	}
	if (str[i + 1] && str.compare(i, com.size(), com)) {
		throw std::runtime_error("Config file error");
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0')
		throw std::runtime_error("Config file error");
	i = i + com.size();
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	temp = str.substr(i, str.size());
	if (str.find(com.c_str(), 0, com.size() - 1)) {
		return (temp);
	} else {
		throw std::runtime_error("Config file error");
	}
}

// TODO
size_t Parser::initLocations(std::vector<std::string> &strings, size_t count, size_t i) {
	std::string temp;
	std::map<std::string, Location> locMap;

	while (count < strings.size()) {
		if (strings[count].find("location:") != std::string::npos) {
			temp = parseLine("location:", strings[count], 2);
			count++;
			Location *newLoc = new Location();
			while (strings[count].find("location:") == std::string::npos && count < strings.size()) {
				if (strings[count] == "\n" || strings[count] == "" || strings[count][0] == '#');
				else if (strings[count].find("root:") != std::string::npos) {
					newLoc->setRoot(parseLine("root:", strings[count], 3));
				} else if (strings[count].find("access-control-allow-methods:") != std::string::npos) {
					newLoc->setAllowMethods(parseLine("access-control-allow-methods:", strings[count], 3));
				} else if (strings[count].find("autoindex:") != std::string::npos) {
					newLoc->setAutoIndex(parseLine("autoindex:", strings[count], 3));
				} else if (strings[count].find("index:") != std::string::npos) {
					newLoc->setIndex(parseLine("index:", strings[count], 3));
				} else if (strings[count].find("cgi_path:") != std::string::npos) {
					newLoc->setCgiPath(parseLine("cgi_path:", strings[count], 3));
				} else if (strings[count].find("client_max_body_size:") != std::string::npos) {
					newLoc->setClientMaxBodySize(parseLine("client_max_body_size:", strings[count], 3));
				} else {
					throw std::runtime_error("Config parser error");
				}
				count++;
			}
			locMap[temp] = *newLoc;
			delete newLoc;
		} else {
			std::cout << "Error: init location" << std::endl;
		}
	}
	_servers[i]->setLocation(locMap);
	return (count);
}

Server *Parser::getServer(std::vector<std::string> &conf, size_t i) {
	Server *newServ = new Server();

	size_t count = 1;
	while (conf[count].find("location:") == std::string::npos && count != conf.size()) {
		if (conf[count] == "\n" || conf[count] == "" || conf[count][0] == '#');
		else if (conf[count].find("host:") != std::string::npos) {
			newServ->setHostAddr(parseLine("host:", conf[count], 1));
		} else if (conf[count].find("port:") != std::string::npos) {
			newServ->setPort(parseLine("port:", conf[count], 1));
		} else if (conf[count].find("server_name:") != std::string::npos) {
			newServ->setServName(parseLine("server_name:", conf[count], 1));
		} else if (conf[count].find("error_page:") != std::string::npos) {
			newServ->setErrorPage(parseLine("error_page:", conf[count], 1));
		} else if (conf[count].find("auth_basic_user_file:") != std::string::npos) {
			newServ->setAuthBasicUserFile(parseLine("auth_basic_user_file:", conf[count], 1));}
		else {
			std::cout << "Error in the parser" << std::endl;
		}
		count++;
	}
	_servers.push_back(newServ);
	if (conf[count].find("location:")) {
		count = initLocations(conf, count, i);
	} else {
		std::cout << "there is not locations" << std::endl;
	}
	if (count != conf.size())
		throw std::runtime_error("Config file error");
	return (_servers[i]);
}
