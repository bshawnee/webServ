#ifndef RESPONSECTORY_H
# define RESPONSEFACTORY_H
# include <string>
# include "AResponse.hpp"
# define AVAILABLE_METHOD_COUNT 4

namespace ft
{

struct Response
{
	typedef ft::AResponse* (*methodFunc)(const std::string& url);
	static ft::AResponse*		accept(const HttpRequest& req);
	static const std::string	availableMethod[AVAILABLE_METHOD_COUNT];
};

};

#endif