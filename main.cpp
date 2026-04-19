#include "Request.hpp"
#include "utils.hpp"

int     main()
{
    std::string  req =  "POST /upload/file.txt?user=mohamed&mode=fast HTTP/1.1\r\n"
                        "Host: localhost:8080\r\n"
                        "User-Agent: Mozilla/5.0\r\n"
                        "Accept: */*\r\n"
                        "Content-Type: application/x-www-form-urlencoded\r\n"
                        "Content-Length: 27\r\n"
                        "Connection: keep-alive\r\n"
                        "\r\n"
                        "name=mohamed&age=21&ok=1";

    Request parser(req);
    std::cout << parser;
}