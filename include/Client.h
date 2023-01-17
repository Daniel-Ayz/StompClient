#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "../include/StompProtocol.h"
#include "../include/event.h"
#include "../include/GameObject.h"



class GameObject;
class StompProtocol;
class ConnectionHandler;

class Client
{
private:
    bool connected;
    std::string activeUsername;
    std::map<std::string,std::map<std::string,GameObject>> gameNamesToUsersToGames;
    StompProtocol& protocol;
    std::map<std::string, int> gamenameToId;
    int idCounter;
    int receiptCounter;
    int waitingForReceiptId;

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