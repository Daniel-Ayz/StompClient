CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -lpthread

all: StompClient

StompClient: bin/ConnectionHandler.o bin/event.o bin/StompClient.o bin/Client.o bin/GameObject.o bin/StompMessage.o bin/StompProtocol.o
	g++ -o bin/StompClient bin/ConnectionHandler.o bin/event.o bin/StompClient.o bin/Client.o bin/GameObject.o bin/StompMessage.o bin/StompProtocol.o $(LDFLAGS)

bin/ConnectionHandler.o: src/ConnectionHandler.cpp
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp

bin/event.o: src/event.cpp
	g++ $(CFLAGS) -o bin/event.o src/event.cpp

bin/StompClient.o: src/StompClient.cpp
	g++ $(CFLAGS) -o bin/StompClient.o src/StompClient.cpp

bin/Client.o: src/Client.cpp
	g++ $(CFLAGS) -o bin/Client.o src/Client.cpp

bin/GameObject.o: src/GameObject.cpp
	g++ $(CFLAGS) -o bin/GameObject.o src/GameObject.cpp

bin/StompMessage.o: src/StompMessage.cpp
	g++ $(CFLAGS) -o bin/StompMessage.o src/StompMessage.cpp

bin/StompProtocol.o: src/StompProtocol.cpp
	g++ $(CFLAGS) -o bin/StompProtocol.o src/StompProtocol.cpp


.PHONY: clean
clean:
	rm -f bin/*
	
