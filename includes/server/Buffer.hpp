#ifndef BUFFER_HPP
# define BUFFER_HPP
# include <list>
# include <string>
# define BUFSIZE 1024
namespace ft
{

class Buffer {
public:
    Buffer() {}
    Buffer(const Buffer& ref) { *this = ref; }
    ~Buffer() {}

    operator bool() { return !(_data.empty()); }
    Buffer& operator=(const Buffer& rhs) {
        if (this == &rhs)
            return *this;
        _data = rhs._data;
        return *this;
    }

    std::string getData(int64_t size = -1) {
        if (size == -1)
            return _data;
        if (_data.length() > static_cast<size_t>(size)) {
            std::string tmp = _data.substr(0, size);
            _data = &_data[size];
            return tmp;
        }
        std::string tmp;
        tmp = _data;
        _data.clear();
        return tmp;
    }

    void addData(const std::string& data) {
        _data += data;
    }
    void addHeader(const std::string& header) {
        std::string tmp = header;
        tmp += _data;
        _data = tmp;
    }

private:
    std::string _data;
};

};

#endif