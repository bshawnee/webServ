#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP
# define DELIMITER			"\r\n\r\n"
# define NEWLINE			"\r\n"
# define HEADER_DELIMITER	":"
# include <map>
# include "../utils.h"

class HttpRequest {
public:

	HttpRequest(std::string const& message);
	HttpRequest();
	HttpRequest(HttpRequest const& ref);
	~HttpRequest();

	HttpRequest&			operator=(HttpRequest const& ref);
	//setters
	void					setRequest(std::string const& message);

	//getters
	std::string const&		getHttpMethod() const;
	std::string const&		getUrl() const;
	std::string	const&		getProtocol() const;
	headers_t const&		getClientHeaders() const;
	//add some getters:
	//getParameters
	std::string const& 		getBody() const; //need fix
	//getOriginalUri // for PATH_INFO //maybe уже есть
	// getHost // in header


	//add server
private:
	std::string		_httpMethod;
	std::string		_url;
	headers_t		_clientHeaders;
	std::string		_protocol;

	std::string		_body;
	//Add Header
};

#endif
