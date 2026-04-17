#include "utils.hpp"


std::string		&pop(std::string& str)
{
	if (str.size())
		str.resize(str.size() - 1);
	return (str);
}

std::string		&to_lower(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return (str);
}

std::string		&to_upper(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	return (str);
}

std::string		&capitalize(std::string &str)
{
	size_t	i = 0;

	to_lower(str);
	str[i] = std::toupper(str[i]);
	while((i = str.find_first_of('-', i + 1)) != std::string::npos)
	{
		if (str[i + 1])
			str[i + 1] = std::toupper(str[i + 1]);
	}
	return (str);
}

std::string		&strip(std::string& str, char c)
{
	size_t	i;

	if (!str.size())
		return str;
	
	i = str.size();
	while (i && str[i - 1] == c)
		i--;
	str.resize(i);

	size_t start = 0;
	while (str[start] == c)	
		start++;
	str = str.substr(start);

	return (str);
}

std::vector<std::string>		split(const std::string &str, char c)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(str);

	while (std::getline(tokenStream, token, c))
		tokens.push_back(token);
	return tokens;
}

bool compare_langs(const std::pair<std::string, float> first, const std::pair<std::string, float> second)
{
  return ( first.second > second.second );
}