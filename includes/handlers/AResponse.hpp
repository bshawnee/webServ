#ifndef ARESPONSE_HPP
# define ARESPONSE_HPP
# include "../server/Buffer.hpp"
# include "../utils.h"
# include "HttpRequest.hpp"
# include <fstream>

namespace ft
{
namespace response
{
class AResponse
{
public:
	AResponse(const AResponse& ref);
	AResponse(HttpRequest& req);

	virtual ft::Buffer	getResponse() = 0;

	AResponse&		operator=(const AResponse& rhs);

	virtual ~AResponse();

	class FailedResponse : public std::invalid_argument
	{
	public:
		FailedResponse(const std::string& errorMsg);
	};
protected:
	ft::Buffer		readFromFile_(const std::string& url);
	void			addHeader(ft::Buffer& buffer);
	std::string		fileType_;
	HttpRequest&	req_;
};

};

};

#endif