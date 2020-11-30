#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <bits/stdc++.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

#include "../message.h"

using namespace std;

class ClientSocket {
private:
  // client socket descriptor
  int clientSocket;

public:
  ClientSocket();

  // set up the client socket
  bool initSocket();

  // executing main loop of the socket
  void mainLoop();

};

#endif // SOCKETCONTROLLER_H
