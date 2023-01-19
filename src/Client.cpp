#include "../include/Client.h"

Client::Client(ConnectionHandler& _connectionHandler, StompProtocol& _protocol) : connected(false), activeUsername("NO USER YET"), gameNamesToUsersToGames(), protocol(_protocol), connectionHandler(_connectionHandler), gamenameToId(), idCounter(0), receiptCounter(0), waitingForReceiptId(-1), shouldTerminateVal(false){
    
}


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
            std::string hostNPort = token;
            size_t posH = hostNPort.find(":");
            std::string host = hostNPort.substr(0, posH);
            std::string port = hostNPort.erase(0, posH + 1);
            s.erase(0, pos + delimiter.length());
            pos = s.find(delimiter);
            token = s.substr(0, pos);
            std::string username = token;
            activeUsername = username;
            s.erase(0, pos + delimiter.length());
            std::string password = s;
            connect();
            
            std::string message = protocol.login(host, username, password);
            std::cout << message << std::endl;
            connectionHandler.sendFrameAscii(message, '\0');
        }
        else if(token == "join"){
            s.erase(0, pos + delimiter.length());
            std::string game_name = s;
            gamenameToId[game_name] = idCounter;
            waitingForReceiptId = receiptCounter;
            std::string message = protocol.join(idCounter++, receiptCounter++, game_name);
            connectionHandler.sendFrameAscii(message, '\0');
        }
        else if(token == "exit"){
            s.erase(0, pos + delimiter.length());
            std::string game_name = s;
            int id = gamenameToId[game_name];
            waitingForReceiptId = receiptCounter;
            std::string message = protocol.exit(id, receiptCounter++);
            connectionHandler.sendFrameAscii(message, '\0');

        }
        else if(token == "report"){
            s.erase(0, pos + delimiter.length());
            std::string file = s;
            std::vector<std::string> messages = protocol.report(activeUsername, parseEventsFile(file));
            for (std::string message : messages){
                connectionHandler.sendFrameAscii(message, '\0');
            }
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
            activeUsername = "NO USER ACTIVE";
            disconnect();
            std::string message = protocol.logout(receiptCounter++);
            connectionHandler.sendFrameAscii(message, '\0');
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
            std::cout << "Login successful" << std::endl;
            waitingForReceiptId = -1;
        }
        else if(token == "RECEIPT"){
            s.erase(0, pos + delimiter.length());
            std::string delimiter2 = ":";
            pos = s.find(delimiter2);
            s.erase(0, pos + delimiter2.length());
            pos = s.find(delimiter);
            int receiptId = std::stoi(s.substr(0, pos));
            if(receiptId == waitingForReceiptId){
                waitingForReceiptId = -1;
            }
            else{
                std::cout << "Got this receipt: " << receiptId << " waited for this receipt: " << waitingForReceiptId << std::endl;
            }
        }
        else if(token == "ERROR"){
            //print the whole frame
            //unblock second thread
            std::cout << response << std::endl;
            terminate();
            waitingForReceiptId = -1;
        }
        else if(token == "MESSAGE"){
            std::cout <<"S:>>>"<< s << std::endl;

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

            if(gameNamesToUsersToGames.count(teamA+"_"+teamB) == 0){
                gameNamesToUsersToGames[teamA+"_"+teamB] = std::map<std::string, GameObject>();
            }
            if(gameNamesToUsersToGames[teamA+"_"+teamB].count(username) == 0){
                gameNamesToUsersToGames[teamA+"_"+teamB][username] = GameObject();
            }
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

void Client::runResponseThread(){
    while(!shouldTerminate()){
        std::string response;
        bool t = connectionHandler.getFrameAscii(response, '\0');
        if(!t){
            std::cout << "teminating" << std::endl;
            terminate();
        }
        std::cout << "got response" << std::endl;
        std::cout << response << std::endl;
        processResponse(response);
    }
}

void Client::runCommandThread(){
    while(!shouldTerminate()){
        std::string input;
        std::getline(std::cin, input);
        processCommand(input);
        waitForResponse();
    }
}

void Client::runMainThread(std::string input){
    std::thread responseThread(&Client::runResponseThread, this);
    processCommand(input);
    waitForResponse();
    runCommandThread();
    responseThread.join();
    std::cout << "Exited Client" << std::endl;
}

void Client::waitForResponse(){
    while(waitingForReceiptId != -1){
        //wait
    }
}

bool Client::shouldTerminate(){
    return shouldTerminateVal;
}

void Client::terminate(){
    shouldTerminateVal = true;
}