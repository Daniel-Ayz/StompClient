#include "../include/GameObject.h"

// update old info to the new, and add new info 
void GameObject::updateGame(const Event& event){
    const std::map<std::string, std::string>&  new_game_updates = event.get_game_updates();

    for (const auto & kv : new_game_updates){
        auto iter = game_updates.find(kv.first);
        if(iter != game_updates.end()){
            iter->second = kv.second;
        }
        else{
            game_updates[kv.first] = kv.second;
        }
    }
    const std::map<std::string, std::string>& new_team_a_updates = event.get_team_a_updates();
    for (const auto & kv : new_team_a_updates ){
        auto iter = team_a_updates.find(kv.first);
        if(iter != team_a_updates.end()){
            iter->second = kv.second;
        }
        else{
            team_a_updates[kv.first] = kv.second;
        }
    }
    const std::map<std::string, std::string>& new_team_b_updates = event.get_team_b_updates();
    for (auto & kv : new_team_b_updates){
        auto iter = team_b_updates.find(kv.first);
        if(iter != team_b_updates.end()){
            iter->second = kv.second;
        }
        else{
            team_b_updates[kv.first] = kv.second;
        }
    }

    events.push_back(event);

}
// print the game summary to the provided file path
void GameObject::summarizeGame(std::string print_file_path){
    //summarizeIT :)
}