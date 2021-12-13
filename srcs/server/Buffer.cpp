#include "../../includes/server/Buffer.hpp"

ft::Buffer::Buffer() : headerSended_(false) {}

ft::Buffer::~Buffer() {
	for (std::list<t_buff>::iterator t = _data.begin(); t != _data.end(); t++) {
		delete[] t->chunk;
	}
}

ft::Buffer::Buffer(const ft::Buffer& ref) : headerSended_(false)
{
	*this = ref;
}

ft::Buffer&	ft::Buffer::operator=(const ft::Buffer& rhs)
{
	if (this == &rhs)
		return *this;
	this->clearBuffer();
	for (std::list<t_buff>::const_iterator it = rhs._data.begin(); it != rhs._data.end(); it++)
	{
		char* tmp = new char [BUFSIZE];
		strcpy(tmp, it->chunk);
		t_buff t = {.chunk = tmp, .length = it->length};
		this->_data.push_back(t);
	}
	return *this;
}

bool	ft::Buffer::headerSended() const
{
	return headerSended_;
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

void	ft::Buffer::addHeader(char *bytes, int length) {
	t_buff t;

	t.chunk = bytes;
	t.length = length;
	_data.push_front(t);
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