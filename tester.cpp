#include <iostream>

	std::string		getBlockHtml(const std::string& html, const std::string& block) {
		std::string endBlock = "</";

		endBlock += &block[1];
		size_t first = html.find(block);
		if (first == std::string::npos)
			return "";
		first += block.size();
		size_t end = html.find(endBlock, first);
		if (end == std::string::npos)
			return "ERROR";
		return html.substr(first, end - first);
	}
int		main()
{
	std::string html = "<html><head><link type=\"stylesheet\" href=\"test.cpp\"></head></html>";
	std::string t = getBlockHtml(html, "<head>");
	std::cout << t << std::endl;
	return 0;
}