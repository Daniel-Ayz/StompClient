#include "../include/StompProtocol.h"
#include "../include/StompMessage.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>


// send CONNECT STOMP message
std::string StompProtocol::login(std::string host, std::string username, std::string password) const{
    std::map<std::string, std::string> headers;
    headers["accept-version"] = "1.2";
    headers["host"] = host;
    headers["login"] = username;
    headers["passcode"] = password;
    StompMessage message("CONNECT", headers, "");
    return message.toString();
}

// send DISCONNECT STOMP message
std::string StompProtocol::logout(int receipt) const{
    std::map<std::string, std::string> headers;
    headers["receipt"] = std::to_string(receipt);
    StompMessage message("DISCONNECT", headers, "");
    return message.toString();
}

// send SUBSCRIBE STOMP message
std::string StompProtocol::join(int id, int receipt, std::string game_name) const{
    std::map<std::string, std::string> headers;
    headers["destination"] = game_name;
    headers["id"] = std::to_string(id);
    headers["receipt"] = std::to_string(receipt);
    StompMessage message("SUBSCRIBE", headers, "");
    return message.toString();
}

// send UNSUBSCRIBE STOMP message
std::string StompProtocol::exit(int id, int receipt) const{
    std::map<std::string, std::string> headers;
    headers["id"] = std::to_string(id);
    headers["receipt"] = std::to_string(receipt);
    StompMessage message("UNSUBSCRIBE", headers, "");
    return message.toString();
}

// send SEND STOMP message for each game event to the <game_name> topic
std::vector<std::string> StompProtocol::report(std::string username, names_and_events _names_and_events) const{
    //std::string team_a_name = _names_and_events.team_a_name;
    //std::string team_b_name = _names_and_events.team_b_name;
    std::vector<std::string> messages;
    std::vector<Event> events = _names_and_events.events;
    for (Event & event: _names_and_events.events){
        std::string message = getEventMessage(username, event);
        messages.push_back(message);
    }
    return messages;
}

// send One event as SEND STOMP message
std::string StompProtocol::getEventMessage(std::string username, Event& event) const{
    std::map<std::string, std::string> headers;
    headers["destination"] = event.get_team_a_name() + "_" + event.get_team_b_name();

    std::string body;
    body = body + "user: " + username + "\n";
    body = body + "team a: " + event.get_team_a_name() + "\n";
    body = body + "team b: " + event.get_team_b_name() + "\n";
    body = body + "event name: " + event.get_name() + "\n";
    body = body + "time: " + std::to_string(event.get_time()) + "\n";
    body = body + "general game updates:\n";
    const std::map<std::string, std::string>&  game_updates = event.get_game_updates();
    for (const auto & kv : game_updates){
        body = body + "\t" + kv.first + ": " + kv.second + "\n";
    }
    body = body + "team a updates:\n";
    const std::map<std::string, std::string>& team_a_updates = event.get_team_a_updates();
    for (const auto & kv : team_a_updates ){
        body = body + "\t" + kv.first + ": " + kv.second + "\n";
    }
    body = body + "team b updates:\n";
    const std::map<std::string, std::string>& team_b_updates = event.get_team_b_updates();
    for (auto & kv : team_b_updates){
        body = body + "\t" + kv.first + ": " + kv.second + "\n";
    }
    body = body + "description:\n";
    body = body + event.get_discription() + "\n";

    StompMessage message("SEND", headers, body);
    return message.toString();
}

Event StompProtocol::receiveEvent(std::string event) const{
    return Event(event);
}
