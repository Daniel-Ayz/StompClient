#include "../include/StompMessage.h"

StompMessage::StompMessage(std::string _command, std::map<std::string, std::string> _headers, std::string _body): command(_command), headers(_headers), body(_body)
{
}

std::string StompMessage::toString(){
    std::string message;
    message = message + command + '\n';
    for (const auto& kv : headers){
        message = message + kv.first + ":" + kv.second + "\n";
    }
    message = message + "\n";
    message = message + body;
    return message;
}