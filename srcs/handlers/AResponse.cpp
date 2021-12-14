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
	int lenBody = 0;
	while (!file.eof())
	{
		char* tmp = new char [BUFSIZE];
		file.read(tmp, BUFSIZE);
		lenBody += file.gcount();
		buf.addData(tmp, file.gcount());
	}
	std::stringstream lenBodyToHeader;
	lenBodyToHeader << lenBody;
	std::string strLen;
	lenBodyToHeader >> strLen;
	std::string header = "HTTP/1.1 200 OK\n" +
	std::string("Server: WebServer\n") +
	"Content-Type: text/html\n" +
	"Content-Length: " + strLen + "\n"
	"Connection-Close: close\n\n";
	char* tmp = new char[header.size()];
	strcpy(tmp, header.c_str());
	buf.addHeader(tmp, header.length());
	return buf;
}

ft::response::AResponse::FailedResponse::FailedResponse(const std::string& errorMsg) :
 std::invalid_argument(errorMsg) {}