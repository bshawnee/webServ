#include "Location.hpp"


Location::Location() {
	_autoIndex = true;
	_clientMaxBodySize = 0;
}

Location::~Location() {
}

void Location::setRoot(const std::string &root) {
	_root = root;
}

void Location::setAutoIndex(std::string autoIndex) {
	if (autoIndex == "on"){
		_autoIndex = true;
	}
	else if (autoIndex == "off"){
		_autoIndex = false;
	}
	else{
		throw std::runtime_error("autoindex error");
	}
}

void Location::setUrl(const std::string &url) {
	_url = url;
}

// TODO
void Location::setAllowMethods(const std::string &methods) {
	std::vector<std::string> strings;
	std::string s;
	std::string tmp = methods;
	std::replace(tmp.begin(), tmp.end(), '\t', ' ');
	std::istringstream f(tmp);

	while (getline(f, s, ' ')) {
		s[s.size()] = '\0';
		strings.push_back(s);
	}
	std::vector<std::string> vec;
	for (size_t i = 0; i < strings.size(); ++i) {
		if (!strings[i].compare("PUT"))
			vec.push_back("PUT");
		else if (!strings[i].compare("GET"))
			vec.push_back("GET");
		else if (!strings[i].compare("HEAD"))
			vec.push_back("HEAD");
		else if (!strings[i].compare("POST"))
			vec.push_back("POST");
		else if (!strings[i].compare("") || !strings[i].compare(" "))
			;
		else
			throw std::runtime_error("methods error");
	}
	if (vec.empty())
		throw std::runtime_error("methods error");
	for (size_t i = 0; i < vec.size(); ++i){
		for (size_t j = i + 1; j < vec.size(); ++j)
			if (vec[i] == vec[j] && i != j)
				throw std::runtime_error("methods error");
	}
	_allowMethods = vec;
}

const std::string &Location::getRoot() const {
	return _root;
}

bool Location::isAutoIndex() const {
	return _autoIndex;
}

const std::string &Location::getUrl() const {
	return _url;
}

const std::vector<std::string> &Location::getAllowMethods() const {
	return _allowMethods;
}

const std::string &Location::getCgiPath() const {
	return _cgiPath;
}

void Location::setCgiPath(const std::string &cgiPath) {
	_cgiPath = cgiPath;
}

size_t Location::getClientMaxBodySize() const
{
	return _clientMaxBodySize;
}

void Location::setClientMaxBodySize(std:: string clientMaxBodySize)
{

	try{
		int temp = std::stoi(clientMaxBodySize);
		if (temp < 0){
			_clientMaxBodySize = 0;
		} else
			_clientMaxBodySize = static_cast<size_t>(temp);
	}
	catch (std::exception &e){
		throw std::runtime_error("setClientMaxBodySize error");
	}
}

const std::string &Location::getIndex() const {
	return _index;
}

void Location::setIndex(const std::string &index) {
	_index = index;
}
