#include "../includes/HttpRequest.hpp"

HttpRequest::HttpRequest() {}

HttpRequest::HttpRequest(HttpRequest const& ref) {
	*this = ref;
}

HttpRequest::HttpRequest(std::string const& message) {
	setRequest(message);
}

HttpRequest::~HttpRequest() {}
#include <iostream>
// TODO Нужно добавить проверки запроса
void					HttpRequest::setRequest(std::string const& message) {
	std::vector<std::string>	parts;
	std::vector<std::string>	heads;
	std::string					head;
	std::vector<std::string>	clientHeaders;

	parts = utils::split(message, NEWLINE);
	head = parts[0];
	heads = utils::split(head, " ");
	// if (heads.size() < 2)
	// 	std::cerr << "Invalid request" << std::endl;
	this->_httpMethod = heads[0];
	this->_url = heads[1];
	this->_protocol = heads[2];
	clientHeaders = utils::split(parts[1], NEWLINE);
	for (size_t i = 0; i < clientHeaders.size(); i++) {
		std::vector<std::string> tmp = utils::split(clientHeaders[i], HEADER_DELIMITER, 2);
		std::pair<std::string, std::string> tmp2;
		tmp2.first = tmp[0];
		tmp2.second = tmp[1];
		this->_clientHeaders.push_back(tmp2);
	}
}

std::string const&		HttpRequest::getHttpMethod() const {
	return this->_httpMethod;
}

std::string const&		HttpRequest::getUrl() const {
	return this->_url;
}

std::string const&		HttpRequest::getProtocol() const {
	return this->_protocol;
}

headers_t const&		HttpRequest::getClientHeaders() const {
	return this->_clientHeaders;
}

HttpRequest&			HttpRequest::operator=(HttpRequest const& ref) {
	if (this == &ref)
		return *this;
	this->_httpMethod = ref._httpMethod;
	this->_protocol = ref._protocol;
	this->_clientHeaders.clear();
	for (size_t i = 0; i < ref._clientHeaders.size(); i++) {
		std::pair<std::string, std::string> tmp;
		tmp.first = ref._clientHeaders[i].first;
		tmp.second = ref._clientHeaders[i].second;
		this->_clientHeaders.push_back(tmp);
	}
	return (*this);
}