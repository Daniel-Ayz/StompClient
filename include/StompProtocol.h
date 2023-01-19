#pragma once

#include "../include/ConnectionHandler.h"
#include "event.h"
struct names_and_events;

// TODO: implement the STOMP protocol
class StompProtocol
{
private:
public:
    // send CONNECT STOMP message
    std::string login(std::string host, std::string username, std::string password) const;
    // send DISCONNECT STOMP message
    std::string logout(int receipt) const;
    // send SUBSCRIBE STOMP message
    std::string join(int id, int receipt, std::string game_name) const;
    // send UNSUBSCRIBE STOMP message
    std::string exit(int id, int receipt) const;
    // send SEND STOMP message for each game event to the <game_name> topic
    std::vector<std::string> report(std::string username, names_and_events names_and_events) const;
    // send One event as SEND STOMP message
    std::string getEventMessage(std::string username, Event& event) const;
    // parse STOMP message to Event Object
    Event receiveEvent(std::string event) const;
};
