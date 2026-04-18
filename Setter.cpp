#include "Request.hpp"
#include "utils.hpp"

void	Request::setBody(const std::string& str)
{
	char	strip[] = {'\n', '\r'};

	this->_body.assign(str);
	int i = 0;
	while (i < 4)
	{
		if (!this->_body.empty() && (this->_body.back() == '\n' || this->_body.back() == '\r'))
			pop(this->_body);
		else
			break ;
		i++;
	}	
}

void	Request::setRet(int ret)
{
	this->_ret = ret;
}

void	Request::setMethod(const std::string &method)
{
	this->_method = method;
}

void		Request::setLang()
{
	std::vector<std::string>	token;
	size_t						i;
	std::map<std::string, std::string>::iterator it;

	it = this->_headers.find("Accept-Language");
	if (it != this->_headers.end())
	{
		token = split(it->second, ',');

		std::vector<std::string>::iterator it_str = token.begin();

		while (it_str != token.end())
		{
			float			weight = 1.0;
			std::string		lang;

			size_t pos = (*it_str).find_first_of("-;");
			lang = (*it_str).substr(0, pos);
			strip(lang, ' ');
	
			size_t qpos = (*it_str).find("q=");
			if (qpos != std::string::npos)
			    weight = atof((*it_str).substr(qpos + 2).c_str());

				
			this->_lang.push_back(std::pair<std::string, float>(lang, weight));
			it_str++;
		}

		this->_lang.sort(compare_langs);
	}
}