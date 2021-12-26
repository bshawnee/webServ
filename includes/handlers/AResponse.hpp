#ifndef ARESPONSE_HPP
# define ARESPONSE_HPP
# include "../server/Buffer.hpp"
# include "HttpRequest.hpp"
# include <fstream>
# include <sstream>
namespace ft
{
namespace response
{
class AResponse
{
public:
	AResponse(const AResponse& ref);
	AResponse(HttpRequest& req);

	virtual ft::Buffer	getRespone() = 0;

	AResponse&		operator=(const AResponse& rhs);

	virtual ~AResponse();

	class FailedResponse : public std::invalid_argument
	{
	public:
		FailedResponse(const std::string& errorMsg);
	};
protected:
	struct responseHeader {
		int				statusCode;
		size_t			contentLength;
		bool			ok;
		std::string		contentType;
		bool			keepConnect;
	};
	typedef int status_t;
	typedef size_t content_t;
	typedef std::string contentType;
	ft::Buffer		readFromFile_(const std::string& url);
	char*			getHttpHeader_(struct responseHeader header);
	HttpRequest&	req_;
};

};

};

#endif