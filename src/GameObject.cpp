#include "../include/GameObject.h"

// GameObject::GameObject(std::string nameA, std::string nameB) : team_a_name(nameA), team_b_name(nameB), game_updates(), team_a_updates(), team_b_updates(){

// }

// update old info to the new, and add new info 
void GameObject::updateGame(const Event& event){
    const std::map<std::string, std::string>&  new_game_updates = event.get_game_updates();
    team_a_name = event.get_team_a_name();
    team_b_name = event.get_team_b_name();

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
    // std::cout << event.to_string() << std::endl;
    events.push_back(event);

}
// print the game summary to the provided file path
void GameObject::summarizeGame(std::string print_file_path){
    //summarizeIT :)
    std::string summary = "";
    summary+=team_a_name+" vs "+team_b_name+"\n";
    summary+="Game stats:\n";
    summary+="General stats:\n";
    for(const auto &kv:game_updates){
        summary+=kv.first+": "+kv.second+"\n";
    }
    summary+=team_a_name+" stats:\n";
    for(const auto &kv:team_a_updates){
        summary+=kv.first+": "+kv.second+"\n";
    }
    summary+=team_b_name+" stats:\n";
    for(const auto &kv:team_b_updates){
        summary+=kv.first+": "+kv.second+"\n";
    }
    summary+="Game event reports:\n";
    //printing the events, check if sort by time is needed
    for(Event &event:events){
        summary+= std::to_string(event.get_time())+" - "+event.get_name()+":\n\n";
        summary+= event.get_discription()+"\n";
    }
    //add game event reports ordered by time
    std::fstream appendFileToWorkWith;
    appendFileToWorkWith.open(print_file_path, std::fstream::in | std::fstream::out | std::fstream::trunc);
    // If file does not exist, Create new file
    if (!appendFileToWorkWith )
    {
        appendFileToWorkWith.open(print_file_path,  std::fstream::in | std::fstream::out | std::fstream::trunc);
        appendFileToWorkWith <<"\n";
        appendFileToWorkWith.close();
    }
    appendFileToWorkWith <<summary;
    appendFileToWorkWith.close();
    std::cout<<"\n";
}