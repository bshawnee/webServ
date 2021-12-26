#ifndef BUFFER_HPP
# define BUFFER_HPP
# include <list>
# include <string>
# include <vector>
# include "../utils.h"
# define BUFSIZE 1024
namespace ft
{

class Buffer {
public:
	typedef std::vector<std::string> t_links;
	typedef struct s_buff {
		char	*chunk;
		size_t	length;
	}			t_buff;

	Buffer();
	Buffer(const ft::Buffer& ref);
	~Buffer();

	operator		bool();
	ft::Buffer&		operator=(const ft::Buffer& rhs);
	std::string		getFullData();
	void			addData(char *bytes, int length);
	void			addHeader(char *bytes, int length);
	bool			headerSended() const;
	void			setHeaderSended(bool status) { headerSended_ = status ; }
	t_buff*			getData();
	void			eraseChunk();
	void			clearBuffer();
	t_links			findRefs() const;

private:
	std::list<t_buff>	_data;
	bool				headerSended_;
};

typedef ft::Buffer (*Handler)(ft::Buffer&);

};

#endif