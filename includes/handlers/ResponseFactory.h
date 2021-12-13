#ifndef RESPONSECTORY_H
# define RESPONSECTORY_H
# include <string>
# include "Get.hpp"
# define AVAILABLE_METHOD_COUNT 4

namespace ft
{
namespace response
{
	typedef ft::response::AResponse* (*methodFunc)(HttpRequest& req);

	ft::response::AResponse*	accept(HttpRequest& req);
};

};

#endif