#include "../../includes/handlers/Get.hpp"


ft::response::Get::Get(const ft::response::Get& ref) : ft::response::AResponse(ref) {}

ft::response::Get::Get(HttpRequest& req) : ft::response::AResponse(req) {}

ft::Buffer	ft::response::Get::getRespone()
{
	return readFromFile_(req_.getUrl());
}