#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <bits/stdc++.h>
#include <guicontroller.h>

#include "message.h"
#include "messagetransceiver.h"

enum GameState {
    NOT_STARTED,
    ONGOING,
    FINISHED
};

using namespace std;

class ClientSocket {
private:
    // client socket descriptor
    int clientSocket;
    string hint;
    GUIController * guiController;

    string username;

    GameState gameState;

    // send message to server
    bool sendMessageToServer(Message message);

    // receive message from server
    bool receiveMessageFromServer(Message &message);

    Message serverResponseHandler(Message message);

    void serverDisconnectedHandler();

public:
    ClientSocket(GUIController * guiController);

    // set up the client socket
    bool initSocket();

    // reset socket
    void resetSocket(int maxClient);

    // executing main loop of the socket
    void mainLoop();

};

#endif // SOCKETCONTROLLER_H
