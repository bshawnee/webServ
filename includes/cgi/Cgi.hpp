#ifndef CGI_HPP
#define CGI_HPP
# include "../handlers/HttpRequest.hpp"
# include "../handlers/AResponse.hpp"
# include "../utils.h"
# include <unistd.h>
# include <map>

# include <iostream>


namespace ft
{
namespace response
{
	class Cgi
	{
	public:
		Cgi(const HttpRequest& req);
		Cgi(const Cgi& ref);
		~Cgi();

		ft::Buffer run(const ft::Buffer& buf);

	private:
		std::map<std::string, std::string> makeMapEnvironment();
		void		setEnv();
		void		setArgs();
//		std::string addContentLength(const std::string& str);
		std::string	addStringToHeader(const std::string& response, const std::string& addedString);
		int			getBodySize(const std::string& response);


		HttpRequest request_;
		char	**env_;
		char	**args_;

	};
};
};




#endif
