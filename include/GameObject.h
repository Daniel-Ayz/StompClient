#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "../include/event.h"
#include <fstream>

class GameObject
{
private:
    // name of team a
    std::string team_a_name;
    // name of team b
    std::string team_b_name;
    // name of the event
    // std::string name;
    // map of all the general game updates
    std::map<std::string, std::string> game_updates;
    // map of all team a updates the second type can be a string bool or int
    std::map<std::string, std::string> team_a_updates;
    // map of all team b updates
    std::map<std::string, std::string> team_b_updates;
    //events
    std::vector<Event> events;
public:
    // GameObject(std::string nameA, std::string nameB);
    // update old info to the new, and add new info 
    void updateGame(const Event& event);
    // print the game summary to the provided file path
    void summarizeGame(std::string print_file_path);
};