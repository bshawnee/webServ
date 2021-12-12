#include "../../includes/handlers/AResponse.hpp"

ft::response::AResponse::AResponse(HttpRequest& req) : req_(req) {}

ft::response::AResponse::AResponse(const ft::response::AResponse& req) : req_(req.req_)
{
	*this = req;
}

ft::response::AResponse&	ft::response::AResponse::operator=(const ft::response::AResponse& rhs)
{
	if (this == &rhs)
		return *this;
	req_ = rhs.req_;
	return *this;
}

ft::Buffer	ft::response::AResponse::readFromFile_(const std::string& url)
{
	std::ifstream file(url);
	if (!file.is_open())
		return readFromFile_("error404.html");
	ft::Buffer buf;
	while (!file.eof())
	{
		char* tmp = new char [BUFSIZE];
		file.read(tmp, BUFSIZE);
		buf.addData(tmp, BUFSIZE);
	}
	return buf;
}

ft::response::AResponse::FailedResponse::FailedResponse(const std::string& errorMsg) :
 std::invalid_argument(errorMsg) {}