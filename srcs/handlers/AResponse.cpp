#include "../../includes/handlers/AResponse.hpp"
# include <iostream>

ft::response::AResponse::AResponse(HttpRequest& req) : req_(req) {}

ft::response::AResponse::AResponse(const ft::response::AResponse& req) : req_(req.req_)
{
	*this = req;
}

ft::response::AResponse::~AResponse() {}

ft::response::AResponse&	ft::response::AResponse::operator=(const ft::response::AResponse& rhs)
{
	if (this == &rhs)
		return *this;
	req_ = rhs.req_;
	return *this;
}

ft::Buffer	ft::response::AResponse::readFromFile_(const std::string& url)
{
	url.c_str();
	std::ifstream file("index.html");
	if (!file.is_open())
		return readFromFile_("error404.html");
	ft::Buffer buf;
	int lenH = strlen("200 OK\n");
	char* header = new char [lenH];
	strcpy(header, "200 OK\n");
	buf.addHeader(header, lenH);
	while (!file.eof())
	{
		char* tmp = new char [BUFSIZE];
		file.read(tmp, BUFSIZE);
		buf.addData(tmp, file.gcount());
	}
	return buf;
}

ft::response::AResponse::FailedResponse::FailedResponse(const std::string& errorMsg) :
 std::invalid_argument(errorMsg) {}