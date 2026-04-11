#include "Request.hpp"
#include "utils.hpp"

Request::~Request() {}


std::vector<std::string>		Request::initMethods()
{
	std::vector<std::string>	methods;

	methods.push_back("GET");
	methods.push_back("POST");
	methods.push_back("DELETE");
    methods.push_back("HEAD");
	methods.push_back("PUT");
	methods.push_back("OPTIONS");

	return methods;
}

std::vector<std::string>	Request::methods = Request::initMethods();

std::string	    Request::nextLine(const std::string &str, size_t& start)
{
	std::string		ret;
	size_t			j;

	if (start == std::string::npos)
		return "";
	j = str.find_first_of('\n', start);
	ret = str.substr(start, j - start);
	if (ret[ret.size() - 1] == '\r')
		pop(ret);
	start = (j == std::string::npos ? j : j + 1);
	return ret;
}


Request::Request(const std::string& str):
	_method (""), _version(""), _ret(200), _body(""), _port(80), _path(""), _query(""), _raw(str)
{
	// this->resetHeaders();
    this->_headers.clear();
	this->_env_for_cgi.clear();
	this->parse(str);
	if (this->_ret != 200)
		std::cerr << "Parse error : " << this->_ret << std::endl;
}

int     Request::parse(const std::string& str)
{
	std::string		key;
	std::string		value;
	std::string		line;
	size_t			i = 0;

	this->FirstLine(nextLine(str, i));
	while ((line = nextLine(str, i)) != "\r" && line != "" && this->_ret != 400)
	{
		key = rKey(line);
		value = rValue(line);
		if (this->_headers.count(key))
				this->_headers[key] = value;
		if (key.find("Secret") != std::string::npos)
			this->_env_for_cgi[format_Header_CGI(key)] = value;
	}
	if (this->_headers["Www-Authenticate"] != "")
		this->_env_for_cgi["Www-Authenticate"] = this->_headers["Www-Authenticate"];
	this->setLang();
	this->setBody(str.substr(i, std::string::npos));
	this->Query();
	return this->_ret;
}

std::string&					strip(std::string& str, char c)
{
	size_t	i;

	if (!str.size())
		return str;
	i = str.size();
	while (i && str[i - 1] == c)
		i--;
	str.resize(i);
	for (i = 0; str[i] == c; i++);
	str = str.substr(i, std::string::npos);
	return str;
}

std::string&	to_lower(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

std::string&	capitalize(std::string &str)
{
	size_t	i = 0;

	to_lower(str);
	str[i] = std::toupper(str[i]);
	while((i = str.find_first_of('-', i + 1)) != std::string::npos)
	{
		if (str[i + 1])
			str[i + 1] = std::toupper(str[i + 1]);
	}
	return str;
}

std::string		Request::rKey(const std::string line)
{
	std::string	ret;
	size_t	i;
	
	i = line.find_first_of(':'); //check
	ret.append(line, 0 , i);
	capitalize(ret);
	return (strip(ret, ' '));
}

std::string		Request::rValue(const std::string line)
{
	size_t i;
	std::string	ret;

	i = line.find_first_of(':');
	i = line.find_first_not_of(' ', i + 1);
	if (i != std::string::npos)
		ret.append(line, i, std::string::npos);
	return (strip(ret, ' '));
}