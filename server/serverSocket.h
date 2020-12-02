#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <bits/stdc++.h>
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h> //close 
#include <arpa/inet.h> //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 

#include "message.h"
#include "playerManager.h"
#include "gamecontroller.h"
#include "messagetransceiver.h"

enum GameState {
    NOT_STARTED,
    ONGOING,
    FINISHED
};

using namespace std;

class ServerSocket {
private:
    // path of the keyword database
    string dbPath;

    // server socket descriptor
    int serverSocket;

    // list of client socket descriptor
    vector<int> clientSocket;

    // maximum number of client
    int maxClient;

    // current number of client
    int nClient;

    // current state of the game
    GameState gameState;

    int currentPlayerIdx;

    // turnState = 0: ask character from client
    // turnState = 1: ask keyword from client
    int turnState;

    PlayerManager playerManager;

    GameController gameController;

    // setup before starting the game
    void startGame();

    // send message to a client
    bool sendMessageToClient(int clientSocket, Message message);

    bool sendMessageToAllClient(Message client);

    // receive message from a client
    bool receiveMessageFromClient(int clientSocket, Message &message);

    // handle when a new client connect to the server
    Message clientConnectedHandler(int clientIdx);

    // handle when a new reponse is received from the server
    void clientResponseHandler(int clientIdx, Message message);

    // handle when a client disconnected from the server
    void clientDisconnectedHandler(int clientIdx);

    void sendGameResultToAllClient();

    // performing a turn (asking char or keyword)
    void nextTurn();

public:
    ServerSocket(int maxClient, string dbPath);

    // set up the server socket
    bool initSocket();

    // executing main loop of the socket
    void mainLoop();
};

#endif // SERVERSOCKET_H
