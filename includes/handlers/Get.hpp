#ifndef GET_HPP
# define GET_HPP
# include "AResponse.hpp"
# include "../../includes/cgi/Cgi.hpp"


namespace ft
{
namespace response
{
class Get : public AResponse
{
public:
	Get(const Get& ref);
	Get(HttpRequest& req);
	Buffer	getResponse();
};

};
};

#endif