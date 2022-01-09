# include "../../includes/handlers/Get.hpp"
# include <sys/stat.h>

ft::response::Get::Get(const ft::response::Get& ref) : ft::response::AResponse(ref) {}

ft::response::Get::Get(HttpRequest& req) : ft::response::AResponse(req) {}

ft::Buffer	ft::response::Get::getResponse() {
	ft::Buffer buffer = readFromFile_(req_.getUrl());
	addHeader(buffer);
	return buffer;

}
