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
	std::string realPathToFile;
	if (url == "/")
		realPathToFile = "index.html";
	else {
		realPathToFile = &url[1];
	}
	std::ifstream file(realPathToFile);
	if (!file.is_open()) {
		return readFromFile_("/404.html");
	}
	ft::Buffer buf;
	std::string tmp;
	while (getline(file, tmp))
		buf.addData(tmp);
	// fileType_ = realPathToFile.substr(realPathToFile.rfind('.') + 1);
	return buf;
}

void ft::response::AResponse::addHeader(ft::Buffer &buffer)
{
	const headers_t& cHeaders = req_.getClientHeaders();
	std::string acceptType;
	std::vector<std::string> splited = utils::split(acceptType, ",");
	std::string strLen = utils::intToString(buffer.getData().length());
	std::string cType = req_.getUrl().substr(req_.getUrl().rfind(".") + 1);
	std::string header = "HTTP/1.1 200 OK\nServer: WebServer\n";
	header += "Content-Length: " + strLen + "\n";
	header += "Connection-Close: close\n\n";
	std::cerr << "---+\n"<< header<< "+---\n" << std::endl;

	buffer.addHeader(header);
}

ft::response::AResponse::FailedResponse::FailedResponse(const std::string& errorMsg) :
 std::invalid_argument(errorMsg) {}
