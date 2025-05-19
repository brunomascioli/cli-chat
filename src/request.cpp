#include "request.h"
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

namespace CliChat 
{


Request::Request(const std::string& payload) 
{
    parse(payload);
}    

void Request::parse(std::string payload) 
{
    try
    {
        json data = json::parse(payload);
        username = data.at("username").get<std::string>();
        message = data.at("message").get<std::string>();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Erro ao parsear JSON: " <<  e.what() << std::endl;
        username = "";
        message = "";
    }
}

std::string_view Request::get_message() const
{
    return message;
}

std::string_view Request::get_username() const 
{
    return username;
}

}