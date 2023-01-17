#include "../include/event.h"
#include "../include/json.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
using json = nlohmann::json;

const std::string WHITESPACE = " \n\r\t\f\v";

Event::Event(std::string team_a_name, std::string team_b_name, std::string name, int time,
             std::map<std::string, std::string> game_updates, std::map<std::string, std::string> team_a_updates,
             std::map<std::string, std::string> team_b_updates, std::string discription)
    : team_a_name(team_a_name), team_b_name(team_b_name), name(name),
      time(time), game_updates(game_updates), team_a_updates(team_a_updates),
      team_b_updates(team_b_updates), description(discription)
{
}

Event::~Event()
{
}

const std::string &Event::get_team_a_name() const
{
    return this->team_a_name;
}

const std::string &Event::get_team_b_name() const
{
    return this->team_b_name;
}

const std::string &Event::get_name() const
{
    return this->name;
}

int Event::get_time() const
{
    return this->time;
}

const std::map<std::string, std::string> &Event::get_game_updates() const
{
    return this->game_updates;
}

const std::map<std::string, std::string> &Event::get_team_a_updates() const
{
    return this->team_a_updates;
}

const std::map<std::string, std::string> &Event::get_team_b_updates() const
{
    return this->team_b_updates;
}

const std::string &Event::get_discription() const
{
    return this->description;
}

Event::Event(const std::string &frame_body) : team_a_name(""), team_b_name(""), name(""), time(0), game_updates(), team_a_updates(), team_b_updates(), description("")
{
    std::string delimiter = "\n";
    std::string delimiter2 = ":";
    std::string s = frame_body;
    size_t pos = 0;
    std::string line;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        line = s.substr(0, pos);

        size_t posInLine = s.find(delimiter2);
        std::string key;
        std::string value;
        bool mapFlag = false;
        if(posInLine != std::string::npos){
            key = line.substr(0, posInLine);
            value = line.erase(0, posInLine + delimiter2.length());
            key = trim(key);
            value = trim(value);
            if(key == "destination"){
                // std::string delimiter3 = "_";
                // size_t posOf_ = value.find(delimiter3);
                // std::string teamA = value.substr(0, posOf_);
                // std::string teamB = value.erase(0, posOf_ + delimiter3.length());
                // team_a_name = teamA;
                // team_b_name = teamB;

                // do nothing (already extracted)
            }
            else if(key == "user"){
                //do nothing (already extracted)
            }
            else if(key == "team a"){
                team_a_name = value;
            }
            else if(key == "team b"){
                team_b_name = value;
            }
            else if(key == "event name"){
                name = value;
            }
            else if(key == "time"){
                time = std::stoi(value);
            }
            else if(key == "general game updates"){
                mapFlag = true;
                s.erase(0, pos + delimiter.length());
                while(s[0] == '\t'){
                    pos = s.find(delimiter);
                    line = s.substr(0, pos);
                    size_t posInLine = s.find(delimiter2);
                    std::string key;
                    std::string value;
                    if(posInLine != std::string::npos){
                        key = line.substr(0, posInLine);
                        value = line.erase(0, posInLine + delimiter2.length());
                        key = trim(key);
                        value = trim(value);
                    }
                    game_updates[key] = value;
                    s.erase(0, pos + delimiter.length());
                }
            }
            else if(key == "team a updates"){
                mapFlag = true;
                s.erase(0, pos + delimiter.length());
                while(s[0] == '\t'){
                    pos = s.find(delimiter);
                    line = s.substr(0, pos);
                    size_t posInLine = s.find(delimiter2);
                    std::string key;
                    std::string value;
                    if(posInLine != std::string::npos){
                        key = line.substr(0, posInLine);
                        value = line.erase(0, posInLine + delimiter2.length());
                        key = trim(key);
                        value = trim(value);
                    }
                    team_a_updates[key] = value;
                    s.erase(0, pos + delimiter.length());
                }
            }
            else if(key == "team b updates"){
                mapFlag = true;
                s.erase(0, pos + delimiter.length());
                while(s[0] == '\t'){
                    pos = s.find(delimiter);
                    line = s.substr(0, pos);
                    size_t posInLine = s.find(delimiter2);
                    std::string key;
                    std::string value;
                    if(posInLine != std::string::npos){
                        key = line.substr(0, posInLine);
                        value = line.erase(0, posInLine + delimiter2.length());
                        key = trim(key);
                        value = trim(value);
                    }
                    team_b_updates[key] = value;
                    s.erase(0, pos + delimiter.length());
                }
            }
            else if(key == "description"){
                s.erase(0, pos + delimiter.length());
                description = s;
                s.erase();
            }
        }
        if(!mapFlag){
            s.erase(0, pos + delimiter.length());
        }
    }
}

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

names_and_events parseEventsFile(std::string json_path)
{
    std::ifstream f(json_path);
    json data = json::parse(f);

    std::string team_a_name = data["team a"];
    std::string team_b_name = data["team b"];

    // run over all the events and convert them to Event objects
    std::vector<Event> events;
    for (auto &event : data["events"])
    {
        std::string name = event["event name"];
        int time = event["time"];
        std::string description = event["description"];
        std::map<std::string, std::string> game_updates;
        std::map<std::string, std::string> team_a_updates;
        std::map<std::string, std::string> team_b_updates;
        for (auto &update : event["general game updates"].items())
        {
            if (update.value().is_string())
                game_updates[update.key()] = update.value();
            else
                game_updates[update.key()] = update.value().dump();
        }

        for (auto &update : event["team a updates"].items())
        {
            if (update.value().is_string())
                team_a_updates[update.key()] = update.value();
            else
                team_a_updates[update.key()] = update.value().dump();
        }

        for (auto &update : event["team b updates"].items())
        {
            if (update.value().is_string())
                team_b_updates[update.key()] = update.value();
            else
                team_b_updates[update.key()] = update.value().dump();
        }
        
        events.push_back(Event(team_a_name, team_b_name, name, time, game_updates, team_a_updates, team_b_updates, description));
    }
    names_and_events events_and_names{team_a_name, team_b_name, events};

    return events_and_names;
}