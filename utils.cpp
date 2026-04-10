#include "utils.hpp"


std::string&		pop(std::string& str)
{
	if (str.size())
		str.resize(str.size() - 1);
	return str;
}