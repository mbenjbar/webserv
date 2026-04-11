#pragma once
#include <iostream>

// CPP Containers
# include <map>
# include <set>
# include <vector>
# include <list>
#include <algorithm>

class Request
{
		private:
			std::string									_method;
			std::string									_version;
			std::map<std::string, std::string>			_headers;
			std::string									_path;
			std::map<std::string, std::string>			_env_for_cgi;
			int											_ret;
			std::string									_body;
			std::string									_query;
			int											_port;
			std::list<std::pair<std::string, float> >	_lang;
			const std::string&							_raw;

			/*** PARSING ***/
			int				FirstLine(const std::string& line);
			std::string		nextLine(const std::string &str, size_t& i);
			int				rPath(const std::string& line, size_t i);
			int				rVersion(const std::string& line, size_t i);
			std::string		rKey(const std::string line);
			std::string		rValue(const std::string line);
			int				Method_check();
			int				Port();
			void			Query();
			std::string 	format_Header_CGI(std::string& key);
			void			setLang();

			


			// https methods that can be used
            
			static	std::vector<std::string>	methods;

			// constructors private
			Request();
			Request(const Request&);

		public:

			Request(const std::string& str); // removed the others so we can only instantiate it with a string
			~Request();
			Request&	operator=(const Request&);

			/*** GETTERS ***/
			const std::map<std::string, std::string>			&get_Headers() const;
			const std::map<std::string, std::string>			&get_Env() const;
			const std::string									&get_Method() const;
			const std::string									&get_Version() const;
			const std::string									&get_Path() const;
			const std::string									&get_Body() const;
			int													get_Port() const;
			const std::string									&get_Query() const;
			int													get_Ret() const;
			const std::string									&get_Raw() const;
			const std::list<std::pair<std::string, float> >		&get_Lang() const;

			/*** SETTERS **/
			void	setMethod(const std::string &method);
			void	setBody(const std::string& line);
			void	setRet(int);

			/*** UTILS ****/
			int				parse(const std::string& str);
			void			resetHeaders();
			void			stripAll();
			void			displayHeaders() const;

			static std::vector<std::string>		initMethods();

};



Request::~Request()
{
}
std::ostream&	operator<<(std::ostream& os, const Request& re);