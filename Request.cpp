#include "Request.hpp"
#include "utils.hpp"

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

Request&	Request::operator=(const Request& obj)
{
	this->_headers = obj.get_Headers();
	this->_env_for_cgi = obj.get_Env();
	this->_method = obj.get_Method();
	this->_version = obj.get_Version();
	this->_ret = obj.get_Ret();
	this->_body = obj.get_Body();
	this->_port = obj.get_Port();
	this->_path = obj.get_Path();

	return (*this);
}

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

void		Request::Query()
{
	size_t		i;

	i = this->_path.find('?');
	if (i != std::string::npos)
	{
		this->_query.assign(this->_path, i + 1, std::string::npos);
		this->_path = this->_path.substr(0, i);
	}
}


std::string 	Request::format_Header_CGI(std::string &key)
{
	size_t i = 0;
	to_upper(key);
	while (i < key.size())
	{
		if (key[i] == '-')
			key[i] = '_';
		i++;
	}
	return ("HTTP_" + key);
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
		if (this->_ret == 400)
			break;
		this->_headers[key] = value;
		if (key.find("Secret") != std::string::npos)
			this->_env_for_cgi[format_Header_CGI(key)] = value; // change this code and forward all headers to CGI
	}
	// if (this->_headers["Www-Authenticate"] != "")
	// 	this->_env_for_cgi["Www-Authenticate"] = this->_headers["Www-Authenticate"];
	this->setLang();
	this->setBody(str.substr(i, std::string::npos));
	this->Query();
	return this->_ret;
}
