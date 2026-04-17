#include "Request.hpp"

std::string		&pop(std::string& str);
std::string 	&to_lower(std::string& str);
std::string		&to_upper(std::string& str);
std::string 	&capitalize(std::string &str);
std::string		&strip(std::string& str, char c);
std::vector<std::string>		split(const std::string &str, char c);
bool compare_langs(const std::pair<std::string, float> first, const std::pair<std::string, float>);