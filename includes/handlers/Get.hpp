#ifndef GET_HPP
# define GET_HPP
# include "AResponse.hpp"

namespace ft
{
namespace response
{
class Get : public AResponse
{
	ft::Buffer	getRespone();
	~Get();
};

};
};

#endif