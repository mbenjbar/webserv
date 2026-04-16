#include "Request.hpp"
#include "utils.hpp"

void	Request::setBody(const std::string& str)
{
	char	strip[] = {'\n', '\r'};

	this->_body.assign(str);
	for (int i = 0; i < 4; i++)
		if (this->_body.size() > 0 && this->_body[this->_body.size() - 1] == strip[i % 2])
			pop(this->_body);
		else
			break ;
}

void	Request::setRet(int ret)
{
	this->_ret = ret;
}

void	Request::setMethod(const std::string &method)
{
	this->_method = method;
}

// void		Request::setLang()
// {
// 	std::vector<std::string>	token;
// 	std::string					header;
// 	size_t						i;

// 	if ((header = this->_headers["Accept-Language"]) != "")
// 	{
// 		token = split(header, ',');
// 		for (std::vector<std::string>::iterator it = token.begin(); it != token.end(); it++)
// 		{
// 			float			weight = 0.0;
// 			std::string		lang;

// 			lang = (*it).substr(0, (*it).find_first_of('-'));
// 			strip(lang, ' ');
// 			if ( (i = lang.find_last_of(';') ) != std::string::npos)
// 			{
// 				weight = atof( (*it).substr(i + 4).c_str() );
// 			}
// 			lang.resize(i > 2 ? 2 : i);
// 			this->_lang.push_back(std::pair<std::string, float>(lang, weight));
// 		}
// 		this->_lang.sort(compare_langs);
// 	}
// }