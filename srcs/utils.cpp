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
namespace parseHtml
{
	std::string		getBlockHtml(const std::string& html, const std::string& block) {
		std::string endBlock = "</";

		endBlock += &block[1];
		size_t first = html.find(block);
		if (first == std::string::npos)
			return "";
		first += block.size();
		size_t end = html.find(endBlock, first);
		if (end == std::string::npos)
			return "";
		return html.substr(first, end - first);
	}
}

}
