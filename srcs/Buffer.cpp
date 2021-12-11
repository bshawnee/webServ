#include "../includes/Buffer.hpp"

ft::Buffer::Buffer() {}

ft::Buffer::~Buffer() {
	for (std::list<t_buff>::iterator t = _data.begin(); t != _data.end(); t++) {
		delete[] t->chunk;
	}
}

ft::Buffer::operator bool() {
	if (_data.begin()->length != BUFSIZE)
		return true;
	else
		return false;
}

void	ft::Buffer::eraseChunk() {
	delete[] _data.begin()->chunk;
	_data.pop_front();
}

void	ft::Buffer::clearBuffer() {
	for (std::list<t_buff>::iterator t = _data.begin(); t != _data.end(); t++)
		delete[] t->chunk;
	_data.clear();
}

void	ft::Buffer::addData(char *bytes, int length) {
	t_buff t;

	t.chunk = bytes;
	t.length = length;
	_data.push_back(t);
}

ft::Buffer::t_buff*		ft::Buffer::getData() {
	return &(*_data.begin());
}

std::string		ft::Buffer::getFullData() {
	std::string data;
	for (std::list<t_buff>::iterator it = _data.begin(); it != _data.end(); it++) {
		data += it->chunk;
	}
	return data;
}