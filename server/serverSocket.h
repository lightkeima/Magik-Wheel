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
// #include "gamecontroller.h"

using namespace std;

class ServerSocket {
private:
//  const int PORT = 7000;
  // server socket descriptor
  int serverSocket;

  // maximum number of client
  int maxClient;

  // list of client socket descriptor
  vector<int> clientSocket;

  // send message to a client
  bool sendMessageToClient(int clientIdx, Message message);

  Message clientConnectedHandler(int clientIdx);

  Message clientResponseHandler(int clientIdx, Message message);
  
  void clientDisconnectedHandler(int clientIdx);  

public:
  ServerSocket(int maxClient);

  // set up the server socket
  bool initSocket();

  // executing main loop of the socket
  void mainLoop();
};

#endif // SERVERSOCKET_H
