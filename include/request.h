#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>

namespace CliChat
{

class Request
{
private:
    std::string username;
    std::string message;
    void parse(std::string payload);
public:
    Request(const std::string& payload);
    std::string get_username() const;
    std::string get_message() const;
};

}

#endif // REQUEST_H