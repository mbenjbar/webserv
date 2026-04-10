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

int		Request::FirstLine(const std::string &str)
{
	size_t	i;
	std::string	line;

	// i = str.find_first_of('\n');
	// line = str.substr(0, i);
	i = line.find_first_of(' ');

	if (i == std::string::npos)
	{
		this->_ret = 400;
		std::cerr << "RFL no space after method" << std::endl;
		return 400;
	}
	this->_method.assign(line, 0, i);
	return this->rPath(line, i);
}

std::string	    Request::nextLine(const std::string &str, size_t& i)
{
	std::string		ret;
	size_t			j;

	if (i == std::string::npos)
		return "";
	j = str.find_first_of('\n', i);
	ret = str.substr(i, j - i);
	if (ret[ret.size() - 1] == '\r')
		pop(ret);
	i = (j == std::string::npos ? j : j + 1);
	return ret;
}