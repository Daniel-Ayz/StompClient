#pragma once

#include <iostream>
#include <map>

class StompMessage
{
private:
    std::string command;
    std::map<std::string, std::string> headers;
    std::string body;

public:
    StompMessage(std::string _command, std::map<std::string, std::string> __headers, std::string body);
    std::string toString();

};
