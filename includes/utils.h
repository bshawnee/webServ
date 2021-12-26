#ifndef UTILS_H
# define UTILS_H
# include <string>
# include <vector>
# include <utility>

typedef std::vector<std::pair<std::string, std::string> > headers_t;

namespace utils
{

std::vector<std::string>	split(std::string const& str, std::string const& delemiter);
std::vector<std::string>	split(std::string const& str, std::string const& delemiter, size_t limit);

};

#endif