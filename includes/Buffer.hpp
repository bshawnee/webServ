#ifndef _BUFFER_HPP
# define _BUFFER_HPP
# include <list>
# include <string>
# define BUFSIZE 1024
# include <iostream>
# include <unistd.h>
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
	std::string		getFullData() {
		std::string data;
		for (std::list<t_buff>::iterator it = _data.begin(); it != _data.end(); it++) {
			write(2, it->chunk, it->length);
			data += it->chunk;

		}

		return data;
	}
	void			addData(char *bytes, int length);
	t_buff*			getData();
	void			eraseChunk();
	void			clearBuffer();
private:
	std::list<t_buff>	_data;
};

}
#endif