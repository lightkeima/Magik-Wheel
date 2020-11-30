#include "clientSocket.h"

ClientSocket::ClientSocket() {

}

bool ClientSocket::initSocket() {
  if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
  { 
    puts("Socket creation error");
    return false; 
  } 
  
  struct sockaddr_in serv_addr; 
  serv_addr.sin_family = AF_INET; 
  serv_addr.sin_port = htons(PORT); 
      
  // Convert IPv4 and IPv6 addresses from text to binary form 
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) { 
    puts("Invalid address/ Address not supported"); 
    return false; 
  } 

  if (connect(clientSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { 
    printf("\nConnection Failed \n"); 
    return false; 
  } 

  return true;
}

void ClientSocket::mainLoop() {
  char *hello = "Hello from client"; 
  send(clientSocket, hello, strlen(hello), 0);
  puts("Hello message sent"); 

  char buffer[MAX_BUFFER+1];
  int valread = read(clientSocket, buffer, 1024); 
  printf("%s\n", buffer); 
}
