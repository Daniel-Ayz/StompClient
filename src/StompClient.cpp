
#include <iostream>
#include <string>
#include "../include/event.h"
#include "../include/StompProtocol.h"
#include <thread>
#include "../include/Client.h"

int main(int argc, char *argv[]) {
	
	while(1){
		std::cout << "Enter login command please" << std::endl;
		std::string input;
		std::getline(std::cin, input);
		std::string delimiter = " ";
		std::string s = input;
		size_t pos = 0;
		std::string token;
		if ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			if(token == "login"){
				s.erase(0, pos + delimiter.length());
				pos = s.find(delimiter);
				token = s.substr(0, pos);
				std::string hostNPort = token;
				size_t posH = hostNPort.find(":");
				std::string host = hostNPort.substr(0, posH);
				std::string port = hostNPort.erase(0, posH + 1);
				s.erase(0, pos + delimiter.length());
				pos = s.find(delimiter);
				token = s.substr(0, pos);
				std::string username = token;
				s.erase(0, pos + delimiter.length());
				std::string password = s;
				ConnectionHandler connectionHandler(host, (short)std::stoi(port));
				if (!connectionHandler.connect()) {
					std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
					return 1;
				}
				StompProtocol protocol;
				Client client(connectionHandler, protocol);
				std::cout << "starting main" << std::endl;
				client.runMainThread(input);
			}
		}
	}

	return 0;
}

// void runCommandThread(Client& c){
//     while(!c.shouldTerminate()){
//         std::string input;
//         std::getline(std::cin, input);
//         c.processCommand(input);
//         c.waitForResponse();
//     }
// }

// void runResponseThread(Client& c){
//     while(!c.shouldTerminate()){
//         std::string response;
//         c.getConnectionHandler()->getFrameAscii(response, '\0');
//         c.processResponse(response);
//     }
// }