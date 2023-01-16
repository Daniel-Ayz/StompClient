
#include <iostream>
#include <string>
#include "../include/event.h"
#include "../include/StompProtocol.h"

class Event;


int main(int argc, char *argv[]) {
	// const std::string text= 
	// "SEND\n"
	// "destination :/ germany_japan\n\n"
	// "user : meni\n"
	// "team a : germany\n"
	// "team b : japan\n"
	// "event name : goal !!!!\n"
	// "time : 1980\n"
	// "general game updates :\n"
	// "team a updates :\n"
	// "\tgoals : 1\n"
	// "\tpossession : 90%\n"
	// "team b updates :\n"
	// "\tpossession : 10%\n"
	// "description :\n"
	// "\"GOOOAAALLL !!! Germany lead !!! Gundogan finally has"
	// "success in the box as he steps up to take the"
	// "penalty , sends Gonda the wrong way , and slots the"
	// "ball into the left - hand corner to put Germany 1 -0"
	// "up ! A needless penalty to concede from Japan's point"
	// "of view , and after a bright start , the Samurai Blues";
	// std::cout << text << std::endl;
	// Event event(text);
	// std::cout << "*************************************************" << std::endl;
	// std::cout << "*************************************************" << std::endl;
	// std::cout << "*************************************************" << std::endl;
	// std::cout << event.get_team_a_name() << std::endl;
	// std::cout << event.get_team_b_name() << std::endl;
	// std::cout << event.get_name() << std::endl;
	// std::cout << event.get_time() << std::endl;
	// const std::map<std::string, std::string>&  game_updates = event.get_game_updates();
    // for (const auto & kv : game_updates){
    //     std::cout << "\t" + kv.first + ": " + kv.second << std::endl;
    // }
    // const std::map<std::string, std::string>& team_a_updates = event.get_team_a_updates();
    // for (const auto & kv : team_a_updates ){
    //     std::cout << "\t" + kv.first + ": " + kv.second << std::endl;
    // }
    // const std::map<std::string, std::string>& team_b_updates = event.get_team_b_updates();
    // for (auto & kv : team_b_updates){
    //     std::cout << "\t" + kv.first + ": " + kv.second << std::endl;
    // }
	// std::cout << event.get_discription() << std::endl;
	// std::cout << "*************************************************" << std::endl;
	// std::cout << "*************************************************" << std::endl;
	// std::cout << "*************************************************" << std::endl;
	// StompProtocol protocol;
	// std::string outMessage = protocol.sendEvent("meni", event);
	// std::cout << outMessage << std::endl;
	// std::cout << "*************************************************" << std::endl;
	// std::cout << "*************************************************" << std::endl;
	// std::cout << "*************************************************" << std::endl;
	// outMessage = protocol.login("1.1.1.1", "meni", "123");
	// std::cout << outMessage << std::endl;
	// std::cout << "*************************************************" << std::endl;
	// std::cout << "*************************************************" << std::endl;
	// std::cout << "*************************************************" << std::endl;
	// outMessage = protocol.logout(73);
	// std::cout << outMessage << std::endl;
	// std::cout << "*************************************************" << std::endl;
	// std::cout << "*************************************************" << std::endl;
	// std::cout << "*************************************************" << std::endl;
	// outMessage = protocol.join(1, 74, "germany_japan");
	// std::cout << outMessage << std::endl;
	// std::cout << "*************************************************" << std::endl;
	// std::cout << "*************************************************" << std::endl;
	// std::cout << "*************************************************" << std::endl;
	// outMessage = protocol.exit(1, 75);
	// std::cout << outMessage << std::endl;

	return 0;
}