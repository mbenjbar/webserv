#include "Request.hpp"
#include "utils.hpp"

std::string		Request::rKey(const std::string line)
{
	size_t end;
	std::string	ret;
	
	end = line.find_first_of(':');
    if (end == std::string::npos || end == 0)
    {
        this->_ret = 400;
        return (ret);
    }
    ret = line.substr(0, end);
	capitalize(ret);
	return (strip(ret, ' '));
}

std::string		Request::rValue(const std::string line)
{
	size_t start;
	std::string	ret;

	start = line.find_first_of(':');
    if (start == std::string::npos)
    {
        this->_ret = 400;
        return (ret);
    }
	start = line.find_first_not_of(' ', start + 1);
    if (start == std::string::npos)
    {
        return (ret);
    }
	ret = line.substr(start);
	return (strip(ret, ' '));
}
