#include "../includes/utils.h"


namespace utils
{

std::vector<std::string>	split(std::string const& str, std::string const& delemiter) {
	size_t lastPos = 0;
	size_t firstPos = 0;
	std::vector<std::string> vec;
	while ((lastPos = str.find(delemiter, firstPos)) != std::string::npos) {
		std::string tmp;
		for (size_t j = firstPos; j < lastPos; j++)
			tmp += str[j];
		vec.push_back(tmp);
		tmp.erase();
		lastPos += delemiter.size();
		firstPos = lastPos;
	}
	if (lastPos != str.size())
		vec.push_back(str.substr(firstPos, lastPos));
	return vec;
}

std::vector<std::string>	split(std::string const& str, std::string const& delemiter, size_t limit) {
	size_t	lastPos = 0;
	size_t	firstPos = 0;
	size_t	count = 1;
	std::vector<std::string> vec;
	while ((lastPos = str.find(delemiter, firstPos)) != std::string::npos && count < limit) {
		std::string tmp;
		for (size_t j = firstPos; j < lastPos; j++)
			tmp += str[j];
		vec.push_back(tmp);
		count++;
		tmp.erase();
		lastPos += delemiter.size();
		firstPos = lastPos;
	}
	if (lastPos != str.size())
		vec.push_back(str.substr(firstPos, lastPos));
	return vec;
}

std::string	intToString(const int num)
{
	std::stringstream containedStream;
	containedStream << num;
	std::string str;
	containedStream >> str;
	return str;
}

}
