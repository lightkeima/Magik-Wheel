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

#include "message.h"

using namespace std;

class ClientSocket {
private:
  // client socket descriptor
  int clientSocket;

  // send message to server
  bool sendMessageToServer(Message message);

  Message serverResponseHandler(Message message);

  void serverDisconnectedHandler();

public:
  ClientSocket();

  // set up the client socket
  bool initSocket();

  // executing main loop of the socket
  void mainLoop();

};

#endif // SOCKETCONTROLLER_H
