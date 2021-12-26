# include "../../includes/handlers/Get.hpp"
# include <sys/stat.h>

ft::response::Get::Get(const ft::response::Get& ref) : ft::response::AResponse(ref) {}

ft::response::Get::Get(HttpRequest& req) : ft::response::AResponse(req) {}

ft::Buffer	ft::response::Get::getResponse() {
	ft::Buffer buffer;
	ft::response::Cgi cgi(req_);

	std::string url = req_.getUrl() + "?phone=88005553535"; // TODO: delete after допиливания cgi


	struct stat fileStruct = {};
	std::string filePath = "docs/html/index.html";
	int fileState = stat(filePath.c_str(), &fileStruct);


	std::string getDefaultCgiPath = ""; // fix
	if ((req_.getUrl().length() > 9 && req_.getUrl().substr(0, 9) == "/cgi-bin/") || (req_.getHttpMethod() == "POST" && !getDefaultCgiPath.empty())) // || allowed extension
//	if (url.find("?") != std::string::npos)
	{
		if (!fileState && !S_ISDIR(fileStruct.st_mode))
			std::cout << "here1\n";
		else
			std::cout << "here2\n";
		buffer = cgi.run(readFromFile_(req_.getUrl()));
	}
	else if (req_.getHttpMethod() == "POST")
	{

	}
	else
	{
		buffer = readFromFile_(req_.getUrl());
		addHeader(buffer);
	}
//	std::cout << buffer.getFullData() << std::endl;
	return buffer;

}