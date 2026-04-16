#include "Request.hpp"
#include "utils.hpp"


int		Request::FirstLine(const std::string &str)
{
	size_t	i;
	std::string	line = str;

	i = line.find_first_of(' ');

	if (i == std::string::npos)
	{
		this->_ret = 400;
		std::cerr << "RFL no space after method" << std::endl;
		return 400;
	}
	this->_method.assign(line, 0, i);
	if (this->Method_check() != 200)
		return(this->_ret);
	return this->rPath(line, i);
}

int		Request::Method_check()
{
	size_t i = 0;
	while (i < this->methods.size())
	{
		if (this->methods[i] == this->_method)
			return this->_ret;
		i++;
	}
	std::cerr << "Invalid method requested" << std::endl;
	this->_ret = 400;
	return this->_ret;
}

int		Request::rPath(const std::string& line, size_t i)
{
	size_t	start;
	size_t	end;

	if ((start = line.find_first_not_of(' ', i)) == std::string::npos)
	{
		this->_ret = 400;
		std::cerr << "No PATH / HTTP version" << std::endl;
		return 400;
	}
	if ((end = line.find_first_of(' ', start)) == std::string::npos)
	{
		this->_ret = 400;
		std::cerr << "No HTTP version" << std::endl;
		return 400;
	}
	this->_path.assign(line, start, end - start);
	return this->rVersion(line, end);
}

int		Request::rVersion(const std::string& line, size_t i)
{
	size_t	start;
	if ((start = line.find_first_not_of(' ', i)) == std::string::npos)
	{
		this->_ret = 400;
		std::cerr << "No HTTP version" << std::endl;
		return 400;
	}
	if (line[start] == 'H' && line[start + 1] == 'T' && line[start + 2] == 'T' &&
			line[start + 3] == 'P' && line[start + 4] == '/')
		this->_version.assign(line, start + 5, 3);
	if (this->_version != "1.0" && this->_version != "1.1")
	{
		this->_ret = 400;
		std::cerr << "BAD HTTP VERSION (" << this->_version << ")" << std::endl;
		return (this->_ret);
	}
	return (this->_ret);
}

