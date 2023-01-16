#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>

class GameObject;
class StompProtocol;
class ConnectionHandler;

class Client
{
private:
    bool connected;
    std::map<std::string,std::map<std::string,GameObject>> gameNamesToUsersToGames;
    StompProtocol& protocol;
public:
    // process command from user keyboard -> send message if needed
    void processCommand(std::string command);
    // process response from server -> print message if needed & save events
    void processResponse(std::string response);
    // set connect state TRUE
    void connect();
    // set connect state FALSE
    void disconnect();
};