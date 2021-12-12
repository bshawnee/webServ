#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP
# define DELIMITER			"\r\n\r\n"
# define NEWLINE			"\r\n"
# define HEADER_DELIMITER	":"
# include "../utils.h"

class HttpRequest {
private:
	std::string		_httpMethod;
	std::string		_url;
	headers_t		_clientHeaders;
	std::string		_protocol;
public:
	HttpRequest();
	HttpRequest(std::string const& message);
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
};

#endif