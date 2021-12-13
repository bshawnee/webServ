#ifndef GET_HPP
# define GET_HPP
# include "AResponse.hpp"

namespace ft
{
namespace response
{
class Get : public AResponse
{
public:
	Get(const Get& ref);
	Get(HttpRequest& req);
	ft::Buffer	getRespone();
};

};
};

#endif