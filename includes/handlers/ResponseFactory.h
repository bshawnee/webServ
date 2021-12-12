#ifndef RESPONSECTORY_H
# define RESPONSECTORY_H
# include <string>
# include "Get.hpp"
# define AVAILABLE_METHOD_COUNT 4


	ft::Buffer	handle(ft::Buffer& b);

namespace ft
{
struct Response
{
	typedef ft::response::AResponse* (*methodFunc)(HttpRequest& req);
	static ft::response::AResponse*		accept(HttpRequest& req);
	static const std::string	availableMethod[AVAILABLE_METHOD_COUNT];
};

};

#endif