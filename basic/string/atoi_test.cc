#include <iostream>
#include <string>

int main() {
    std::string str =  "200 OK\r\n"
                        "accept-ranges: bytes\r\n"
                        "cache-control: max-age=86400\r\n"
                        "connection: keep-alive\r\n"
                        "content-length: 81\r\n"
                        "content-type: text/html\r\n"
                        "date: Sat, 20 Mar 2021 05:48:53 GMT\r\n"
                        "etag: \"51-47cf7e6ee8400\"\r\n"
                        "expires: Sun, 21 Mar 2021 05:48:53 GMT\r\n"
                        "keep-alive: timeout=4\r\n"
                        "last-modified: Tue, 12 Jan 2010 13:48:00 GMT\r\n"
                        "proxy-connection: keep-alive\r\n"
                        "server: Apache\r\n\r\n"
                        "<html>\r\n"
                        "<meta http-equiv=\"refresh\" content=\"0;url=http://www.baidu.com/\">\r\n"
                        "</html>\r\n";

    std::cout << atoi(str.c_str()) << std::endl;
    
}