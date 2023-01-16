#pragma once

#include "../include/ConnectionHandler.h"
#include "event.h"
struct names_and_events;

// TODO: implement the STOMP protocol
class StompProtocol
{
private:
    ConnectionHandler& connectionHandler;
public:
    StompProtocol(ConnectionHandler& connectionHandler);
    // send CONNECT STOMP message
    void login(std::string host, std::string username, std::string password);
    // send DISCONNECT STOMP message
    void logout(int receipt);
    // send SUBSCRIBE STOMP message
    void join(int id, int receipt, std::string game_name);
    // send UNSUBSCRIBE STOMP message
    void exit(int id, int receipt);
    // send SEND STOMP message for each game event to the <game_name> topic
    void report(std::string username, names_and_events names_and_events);
    // send One event as SEND STOMP message
    void sendEvent(std::string username, Event& event) const;
    // parse STOMP message to Event Object
    Event receiveEvent(std::string event);
};
