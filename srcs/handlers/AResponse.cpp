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
	std::ifstream file("docs/html/index.html");
	if (!file.is_open())
		return readFromFile_("error404.html");
	ft::Buffer buf;
	int lenBody_ = 0; // may be delete?
	while (!file.eof())
	{
		char* tmp = new char [BUFSIZE];
		file.read(tmp, BUFSIZE);
		lenBody_ += file.gcount();
		buf.addData(tmp, file.gcount());
	}
	return buf;
}

void ft::response::AResponse::addHeader(ft::Buffer &buffer)
{
	std::string strLen = utils::intToString(buffer.getFullData().length());
//	std::string strLen = utils::intToString(264);
	std::string header = "HTTP/1.1 200 OK\n" +
						 std::string("Server: WebServer\n") +
						 "Content-Type: text/html\n" +
						 "Content-Length: " + strLen + "\n"
													   "Connection-Close: close\n\n";
	char* tmp = new char[header.size()];
	strcpy(tmp, header.c_str());
	buffer.addHeader(tmp, header.length());
}

ft::response::AResponse::FailedResponse::FailedResponse(const std::string& errorMsg) :
 std::invalid_argument(errorMsg) {}