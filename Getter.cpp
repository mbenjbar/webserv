#include "Request.hpp"
#include "utils.hpp"

const std::map<std::string, std::string>	&Request::get_Headers() const {return this->_headers;}


const std::map<std::string, std::string>	&Request::get_Env() const {return this->_env_for_cgi;}


const std::string	&Request::get_Method() const {return this->_method;}


const std::string	&Request::get_Version() const {return this->_version;}


const std::string	&Request::get_Body() const {return this->_body;}


const std::string	&Request::get_Path() const {return this->_path;}


const std::string	&Request::get_Query() const {return this->_query;}


const std::string	&Request::get_Raw() const {return this->_raw;}


int 	Request::get_Ret() const {return this->_ret;}


int		Request::get_Port() const {return this->_port;}


const std::list<std::pair<std::string, float> >	&Request::get_Lang() const {return this->_lang;}