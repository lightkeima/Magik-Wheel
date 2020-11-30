#ifndef GAMEFLOW_H
#define GAMEFLOW_H

#define HEADER_UNAME_REQUEST    "USERNAME_REQUEST"
#define HEADER_UNAME_RESPONSE   "USERNAME_RESPONSE"
#define HEADER_UNAME_INVALID    "USERNAME_INVALID"
#define HEADER_UNAME_DUPLICATED "USERNAME_DUPLICATED"
#define HEADER_REGISTER_SUCCESS "REGISTER_SUCCESS"
#define HEADER_BAD_MESSAGE      "BAD_MESSAGE"
#define HEADER_SERVER_FULL      "SERVER_FULL"

#include <bits/stdc++.h>
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h> //close 
#include <arpa/inet.h> //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 

#include "gamecontroller.h"
#include "serverSocket.h"

using namespace std;

struct Player {
  int id;
	string username;

	Player();
};

class PlayerManager {
private:
	vector<Player> players;
	int maxPlayer;
  int currentID;
  
public:
  PlayerManager();
  
	PlayerManager(int maxPlayer);

	bool isValidUsername(string username);

	bool isDuplicatedUsername(string username);

	void registerPlayer(int playerIdx, string username);

  void sortPlayerByRegisterTime();

  int getNextPlayerIndex();
};

struct Message {
	string header;
	vector<string> data;

	Message(string header);

	Message(string header, vector<string> data);

	Message(char* buffer);

	const char* c_str();
};

class GameFlow {
private:
  // required number of player
  int maxPlayer;
  
  ServerSocket server;
	
  PlayerManager playerManager;

  GameController gameController;

  // return appropriate response upon receiving client's request
  const char* getServerResponse(int playerIdx, char* buffer);

public:
  GameFlow(int maxPlayer);

  Message clientConnectedHandler();

  Message clientDisconnectedHandler();

  Message clientResponseHandler();


};

#endif // GAMEFLOW_H
