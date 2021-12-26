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
	std::string htmlPath = "." + url;
	if (htmlPath == "./")
		htmlPath = "/index.html";
	std::ifstream file(htmlPath);
	if (!file.is_open())
		return readFromFile_("/404.html");
	ft::Buffer buf;
	size_t lenBody = 0;
	while (!file.eof())
	{
		char* tmp = new char [BUFSIZE];
		file.read(tmp, BUFSIZE);
		lenBody += file.gcount();
		buf.addData(tmp, file.gcount());
	}
	responseHeader t = {
		.statusCode = 200,
		.contentLength = lenBody,
		.ok = true,
		.keepConnect = false,
		.contentType = "text/" + std::string(&url[url.rfind('.') + 1])
	};
	std::cerr << "========" << &url[url.rfind('.')] << std::endl;
	if (url.rfind(".css") != std::string::npos)
		t.contentType = "text/css";
	else if (url.rfind(".js") != std::string::npos)
		t.contentType = "test/js";
	char* headHttp = getHttpHeader_(t);
	buf.addHeader(headHttp, strlen(headHttp));
	file.close();
	return buf;
}

char*			ft::response::AResponse::getHttpHeader_(struct responseHeader header)
{
	std::stringstream headerStream;
	headerStream << "HTTP/1.1 " << header.statusCode << " ";
	if (header.ok)
		headerStream << "OK\n";
	else
		headerStream << "KO\n";
	headerStream << "Content-Type: " << header.contentType << "\n"
	<< "Content-Length: " << header.contentLength << "\n";
	headerStream << "Connection-Close: ";
	if (header.keepConnect)
		headerStream << "keep-alive\n\n";
	else
		headerStream << "close\n\n";
	std::string tmp = headerStream.str();
	char* buf = new char[tmp.length()];
	strcpy(buf, tmp.c_str());
	return buf;
}
ft::response::AResponse::FailedResponse::FailedResponse(const std::string& errorMsg) :
 std::invalid_argument(errorMsg) {}