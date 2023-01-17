#include "../include/Client.h"

// process command from user keyboard -> send message if needed
void Client::processCommand(std::string command){
    std::string delimiter = " ";
    std::string s = command;
    size_t pos = 0;
    std::string token;
    if ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if(token == "login"){
            s.erase(0, pos + delimiter.length());
            pos = s.find(delimiter);
            token = s.substr(0, pos);
            std::string host = token;
            s.erase(0, pos + delimiter.length());
            pos = s.find(delimiter);
            token = s.substr(0, pos);
            std::string username = token;
            s.erase(0, pos + delimiter.length());
            std::string password = s;
            connect();
            protocol.login(host, username, password);
        }
        else if(token == "join"){
            s.erase(0, pos + delimiter.length());
            std::string game_name = s;
            gamenameToId[game_name] = idCounter;
            waitingForReceiptId = receiptCounter;
            protocol.join(idCounter++, receiptCounter++, game_name);
        }
        else if(token == "exit"){
            s.erase(0, pos + delimiter.length());
            std::string game_name = s;
            int id = gamenameToId[game_name];
            waitingForReceiptId = receiptCounter;
            protocol.exit(id, receiptCounter++);
        }
        else if(token == "report"){
            s.erase(0, pos + delimiter.length());
            std::string file = s;
            protocol.report(activeUsername, parseEventsFile(file));
        }
        else if(token == "summary"){
            s.erase(0, pos + delimiter.length());
            pos = s.find(delimiter);
            token = s.substr(0, pos);
            std::string gamename = token;
            s.erase(0, pos + delimiter.length());
            pos = s.find(delimiter);
            token = s.substr(0, pos);
            std::string username = token;
            s.erase(0, pos + delimiter.length());
            std::string file = s;
            gameNamesToUsersToGames[gamename][username].summarizeGame(file);
        }
    }
    else if(s == "logout"){
            waitingForReceiptId = receiptCounter;
            disconnect();
            protocol.logout(receiptCounter++);
    }
    //block thread and wait for response

}

// process response from server -> print message if needed & save events
void Client::processResponse(std::string response){
    std::string delimiter = "\n";
    std::string s = response;
    size_t pos = 0;
    std::string token;
    if ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if(token == "CONNECTED"){
            //print login GREAT SUCCESS
            //unblock second thread
        }
        else if(token == "RECEIPT"){
            s.erase(0, pos + delimiter.length());
            std::string delimiter2 = ":";
            pos = s.find(delimiter2);
            s.erase(0, pos + delimiter2.length());
            pos = s.find(delimiter);
            int receiptId = std::stoi(s.substr(0, pos));
            if(receiptId == waitingForReceiptId){
                //unblock second thread
            }
            else{
                //error?
            }
        }
        else if(token == "ERROR"){
            //print the whole frame
            //unblock second thread
        }
        else if(token == "MESSAGE"){
            pos = s.find(delimiter+delimiter);
            s.erase(0, pos + delimiter.length()*2);
            std::string frameBody = s;

            std::string userDelimiter = "user:";
            pos = s.find(userDelimiter);
            s.erase(0, pos + userDelimiter.length());
            pos = s.find(delimiter);
            std::string username = s.substr(0, pos);
            username = trim(username);

            std::string teamAdelimiter = "team a:";
            pos = s.find(teamAdelimiter);
            s.erase(0, pos + teamAdelimiter.length());
            pos = s.find(delimiter);
            std::string teamA = s.substr(0, pos);
            teamA = trim(teamA);

            std::string teamBdelimiter = "team b:";
            pos = s.find(teamBdelimiter);
            s.erase(0, pos + teamBdelimiter.length());
            pos = s.find(delimiter);
            std::string teamB = s.substr(0, pos);
            teamB = trim(teamB);

            gameNamesToUsersToGames[teamA+"_"+teamB][username].updateGame(Event(frameBody));
        }
    }
}

// set connect state TRUE
void Client::connect(){
    //check if already connected and if so print >:(
    connected = true;
}

// set connect state FALSE
void Client::disconnect(){
    connected = false;
}