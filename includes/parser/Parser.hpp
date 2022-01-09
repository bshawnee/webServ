#ifndef PARSER_HPP
#define PARSER_HPP

#include <fstream>
#include <iostream>
#include "Server_Instance.hpp"
#include <vector>
#include <string>

class Parser {
private:
	std::vector<Server *> _servers;
	Parser(const Parser &other);
	Parser &operator=(const Parser &other);

	void parseConfig(std::ifstream &fd);

	size_t	initLocations(std::vector<std::string> &strings, size_t count, size_t i);
	Server	*getServer(std::vector<std::string> &conf, size_t i);
	void	validateConfig();

public:
	Parser(const std::string &fileName);
	virtual ~Parser();
	const std::vector<Server *> &getServers() const;
};


#endif
