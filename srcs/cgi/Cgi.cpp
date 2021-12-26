# include "../../includes/cgi/Cgi.hpp"

ft::response::Cgi::Cgi(const Cgi &ref)
{
	this->request_ = ref.request_;
	env_ = ref.env_;//need deep copy
	args_ = ref.args_;
}

ft::response::Cgi::Cgi(const HttpRequest &req)
{
	this->request_ = req;
	setArgs();
	setEnv();
}

ft::response::Cgi::~Cgi()
{
	int i = 0;
	while (env_[i])
		free(env_[i++]);
	delete [] env_;
	free(args_[0]);
	delete [] args_;
}

ft::Buffer ft::response::Cgi::run(const ft::Buffer &pageBeforeCgi)
{

	ft::Buffer responsePage = pageBeforeCgi;
	// иногда приходит странный буфер
	std::cout << "---------------\n";
	std::cout << responsePage.getFullData() << std::endl;
	std::cout << "---------------\n";
	int fdRequest[2];
	int fdResponse[2];
	pid_t pid;
	int status = 0;

	if (pipe(fdRequest) == -1 || pipe(fdResponse) == -1)
		throw std::exception(); // exception??



	int i = 0;
	while (env_[i])
	{
		std::cout << env_[i++] << std::endl;
	}
	pid = fork();
	if (pid < 0)
		throw std::exception(); // exception??
	else if (pid == 0)
	{
		const std::string page = responsePage.getFullData();
		write(fdRequest[1], page.c_str(), page.length());
		dup2(fdRequest[0], 0);
		dup2(fdResponse[1], 1);

		close(fdRequest[1]);
		close(fdResponse[0]);

		status = execve(args_[0], args_, env_);
		close(fdRequest[0]);
		close(fdResponse[1]);
		exit(status);
	}
	close(fdRequest[0]);
	close(fdRequest[1]);
	close(fdResponse[1]);
	waitpid(pid, &status, 0);



//  может быть сделать иначе?
	char	tmp = 'a';
	std::string toBuffer("");
	while (int fd = read(fdResponse[0], &tmp, 1))
		toBuffer += std::string(1, tmp);
	close(fdResponse[0]);

	// TODO: check if content-length exists
	//added contentLength to response
	toBuffer = "HTTP/1.1 " + toBuffer;
	std::string contentLength("Content-Length: " + utils::intToString(getBodySize(toBuffer)) + "\r\n");
//	std::string contentLength("Content-Length: " + utils::intToString(264) + "\r\n");
	toBuffer = addStringToHeader(toBuffer, "Server: WebServer\r\n");
	toBuffer = addStringToHeader(toBuffer, contentLength);
	toBuffer = addStringToHeader(toBuffer, "Connection-Close: close\r\n");
	//add date


	responsePage.clearBuffer();
	responsePage.addData(strdup(toBuffer.c_str()), toBuffer.length());


//	std::cout << responsePage.getFullData();
	return responsePage;
}



std::string ft::response::Cgi::addStringToHeader(const std::string& response, const std::string& addedString)
{
	int pos = response.find("\r\n\r\n") + 2;
	std::string newResponse (response.substr(0, pos) + addedString + response.substr(pos));
	return newResponse;
}

int ft::response::Cgi::getBodySize(const std::string& response)
{
	int pos = response.find("\r\n\r\n") + 4;
	return response.substr(pos).length();
}

// все переделать
std::map<std::string, std::string>	ft::response::Cgi::makeMapEnvironment()
{
	std::map<std::string, std::string> mapEnv;
	char buf[1024];
	std::string absolutePath = getcwd(buf, 1024);


	mapEnv["SERVER_SOFTWARE"] = "WebServ/1.0";
	mapEnv["SERVER_PROTOCOL"] = "HTTP/1.1";
	mapEnv["GATEWAY_INTERFACE"] = "CGI/1.1";
	mapEnv["AUTH_TYPE"] = ""; // может удалить?


	// не ноль в методе POST and DELETE, нужна для определнения количества символов, которые нужно считать скрипту
	// из своего инпута
//	mapEnv["CONTENT_LENGTH"] = utils::intToString(request_.getBody().length());
	mapEnv["CONTENT_LENGTH"] = "0"; // from request(body) если есть for POST
	mapEnv["CONTENT_TYPE"] = "application/x-www-form-urlencoded"; // from header
	mapEnv["QUERY_STRING"] = ""; // from request
//	mapEnv["QUERY_STRING"] = "phone=88005553535"; // from request

//	mapEnv["SCRIPT_NAME"] = "cgi-bin/cgi_tester"; // хз
	mapEnv["SCRIPT_FILENAME"] = "cgi-bin/cgi_tester"; // хз
//	mapEnv["SCRIPT_NAME"] = "cgi_tester"; // хз
//	mapEnv["PATH_INFO"] = request_.getUrl() + "?phone=88005553535"; // from request // originalUri + cgiParams from request
//std::string tmp1("/cgi-bin/"); //
//	mapEnv["PATH_INFO"] = tmp1 + "?phone=88005553535"; // from request // originalUri + cgiParams from request
	mapEnv["PATH_INFO"] = "/docs/html/"; // from request // originalUri + cgiParams from request // что вызывается в строке
//	if (!mapEnv["QUERY_STRING"].empty())
//		mapEnv["PATH_INFO"] = mapEnv["PATH_INFO"] + "?" + mapEnv["QUERY_STRING"];
//	mapEnv["PATH_INFO"] = request_.getUrl();
//	std::cout << "URL is " << request_.getUrl() << std::endl;
	mapEnv["PATH_TRANSLATED"] = absolutePath + mapEnv["PATH_INFO"];

//	mapEnv["REMOTE_ADDR"] = "127.0.0.1"; // from header
//	mapEnv["REMOTE_HOST"] = "localhost"; // from header
//	mapEnv["REMOTE_IDENT"] = "";
//	mapEnv["REMOTE_USER"] = ""; // from header
//	mapEnv["REQUEST_METHOD"] = request_.getHttpMethod();
	mapEnv["REQUEST_METHOD"] = "POST";
	mapEnv["SERVER_NAME"] = "webserv"; // from server
	mapEnv["SERVER_PORT"] = "30000"; // from server

	mapEnv["HTTP_ACCEPT"]="*/*";
	mapEnv["HTTP_ACCEPT_ENCODING"]="gzip, deflate";
	mapEnv["HTTP_CACHE_CONTROL"]="no-cache";
	mapEnv["HTTP_CONNECTION"]="keep-alive";
	mapEnv["HTTP_CONTENT_LENGTH"]="0";
	mapEnv["HTTP_HOST"]="localhost:30000";
	mapEnv["HTTP_USER_AGENT"]="PostmanRuntime/7.3.0";
	mapEnv["REMOTE_ADDR"]="localhost";
	mapEnv["REMOTE_IDENT"]="";
	mapEnv["REMOTE_USER"]="";
	mapEnv["REQUEST_FILENAME"]="/docs/html/";
	mapEnv["REQUEST_URI"]="/docs/html/";


	return mapEnv;
}

void	ft::response::Cgi::setEnv()
{
	int mapLength;

	std::map<std::string, std::string> mapEnv = makeMapEnvironment(); // create map with environment
	mapLength = mapEnv.size();
	env_ = new char*[mapLength + 1];
	int i = 0;

	for (std::map<std::string, std::string>::const_iterator it = mapEnv.begin(); it != mapEnv.end(); it++)
	{
		std::string tmp = it->first + "=" + it->second;
		env_[i] = strdup(tmp.c_str());
		i++;
	}
	env_[i] = nullptr;
}

void ft::response::Cgi::setArgs()
{
	args_ = new char*[2];
	std::string sgiPath("/Users/rbooker/Projects/webServ/cgi-bin/cgi_tester");
	args_[0] = strdup(sgiPath.c_str()); // sgiPath
	args_[1] = nullptr;

}



