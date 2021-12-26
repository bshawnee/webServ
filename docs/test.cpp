#include <iostream>
# include <fcntl.h>
# include <unistd.h>

int main()
{
	char	tmp = 'a';

	while (int fd = read(0, &tmp, 1))
	{
		write(1, &tmp, 1);
	}

//	std::cout << "hello world" << std::endl;
}