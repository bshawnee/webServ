#include "../../includes/handlers/Post.hpp"

ft::response::Post::Post(const ft::response::Post& ref) : ft::response::AResponse(ref) {}

ft::response::Post::Post(HttpRequest& req) : ft::response::AResponse(req) {}

ft::Buffer	ft::response::Post::getResponse()
{
	return readFromFile_(req_.getUrl());
}