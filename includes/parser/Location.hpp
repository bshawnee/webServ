#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>
#include <iostream>
#include <vector>
#include <sstream>

class Location {
private:
	std::string					_root;
	bool						_autoIndex;
	std::string					_url;
	std::vector<std::string>	_allowMethods;
	std::string 				_cgiPath;
	size_t 						_clientMaxBodySize;
	std::string 				_index;

public:
	Location();
	virtual ~Location();

	void setRoot(const std::string & root);
	void setUrl(const std::string & url);
	void setIndex(const std::string &index);
	void setAutoIndex(std::string autoIndex);
	void setAllowMethods(const std::string & allowMethods);
	void setClientMaxBodySize(std::string clientMaxBodySize);
	void setCgiPath(const std::string &cgiPath);

	bool getAutoIndex() const { return _autoIndex;}
	const std::string &getRoot() const;
	const std::string & getUrl() const;
	const std::vector<std::string> & getAllowMethods() const;
	const std::string & getIndex() const;
	size_t getClientMaxBodySize() const;
	const std::string &getCgiPath() const;

	bool isAutoIndex() const;
};

#endif
