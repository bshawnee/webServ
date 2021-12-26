#ifndef POST_HPP
#define POST_HPP


# include "AResponse.hpp"

namespace ft
{
namespace response
{
class Post : public AResponse
{
	public:
	Post(const Post& ref);
	Post(HttpRequest& req);
	ft::Buffer	getResponse();
};

};
};

#endif
