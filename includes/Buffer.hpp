#ifndef BUFFER_HPP
# define BUFFER_HPP
# include <list>
# include <string>
# define BUFSIZE 10
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
	std::string		getFullData();
	void			addData(char *bytes, int length);
	t_buff*			getData();
	void			eraseChunk();
	void			clearBuffer();
private:
	std::list<t_buff>	_data;
};

};

#endif