#ifndef _BUFFER_HPP
# define _BUFFER_HPP
# include <list>
# include <string>
# define BUFSIZE 12
namespace ft
{

class Buffer {
public:
	typedef struct s_buff {
		char	*chunk;
		size_t	length;
	}			t_buff;
	Buffer();
	// TODO добавить хренатень
	~Buffer();

	operator bool();
	void			addData(char *bytes, int length);
	t_buff*			getData();
	void			eraseChunk();
	void			clearBuffer();
private:
	std::list<t_buff>	_data;
};

}
#endif