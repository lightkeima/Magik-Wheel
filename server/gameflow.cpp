#include "socketController.h"


Player::Player() {
	username = "";
	id = -1;
}

PlayerManager::PlayerManager() {}

PlayerManager::PlayerManager(int maxPlayer) {
	this->maxPlayer = maxPlayer;
	players.assign(maxPlayer, Player());
}

bool PlayerManager::isValidUsername(string username) {
	if (username.length() > 10)
		return false;
	for(char c: username) {
		if (!isalnum(c) && c != '_')
			return false;
	}
	return true;
}

bool PlayerManager::isDuplicatedUsername(string username) {
	for(int i = 0; i < maxPlayer; ++i) {
		if (players[i].id != -1 && players[i].username == username)
			return false;
	}
	return true;
}

void PlayerManager::registerPlayer(int playerIdx, string username) {
	players[playerIdx].id = ++currentID;
	players[playerIdx].username = username;
}


Message::Message(string header) {
	this->header = header;
}

Message::Message(string header, vector<string> data) {
	this->header = header;
	this->data = data;
}

Message::Message(char* buffer) {
	string __tmp(buffer);
	stringstream ss(__tmp);
	string token;		
	while (ss >> token) {
		if (header == "")
			header = token;
		else
			data.push_back(token);
	}
}

const char* Message::c_str() {
	stringstream ss;
	ss << header;
	for (string token: data)
		ss << " " << token;
	return ss.str().c_str();
}


Server::Server(int maxPlayer) {	
	this->maxPlayer = maxPlayer;
	playerManager = PlayerManager(maxPlayer);
}

bool Server::initServerSocket() {
	// create a server socket 
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		puts("Create socket failed");
		return false;
	}

	// set server socket to allow multiple connections
	int opt = true;
	if(setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0) {
		puts("Set socket option failed");
		return false;
	}
	
	// type of socket created 
	sockaddr_in address;	 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons(PORT);

	// bind the socket to localhost port 8888 
	if (bind(serverSocket, (struct sockaddr*)&address, sizeof(address)) < 0) {
		puts("Bind socket to localhost failed");
		return false;
	}
		
	// try to specify maximum of 3 pending connections for the server socket
	if (listen(serverSocket, 3) < 0) {
		puts("Listen failed");
		return false;
	}

	return true;
}

const char* Server::getServerResponse(int playerIdx, char* __buffer) {
	Message message(__buffer);

	string header;
	vector<string> data;

	if (message.header == HEADER_UNAME_RESPONSE) {
		if (data.size() != 1) { // Bad syntax
			header = HEADER_BAD_MESSAGE;			
		}
		else {
			string username = data[0];
			if (!playerManager.isValidUsername(username)) {
				header = HEADER_UNAME_INVALID;
			} 
			else if (playerManager.isDuplicatedUsername(username)) {
				header = HEADER_UNAME_DUPLICATED;
			} 
			else {
				playerManager.registerPlayer(playerIdx, username);
				header = HEADER_REGISTER_SUCCESS;
			}
		}
	} 
	else { // Unknown syntax -> Bad syntax
		header = HEADER_BAD_MESSAGE;
	} 

	return Message(header, data).c_str();
}
	
void Server::serverMainLoop() {
	printf("Waiting for players...");

	clientSocket.assign(maxPlayer, 0);
	
	while (true) {
		fd_set readfds; 
		// clear the socket set 
		FD_ZERO(&readfds);
		// add master socket to set 
		FD_SET(serverSocket, &readfds);
		
		// highest file descriptor number, need it for the select function 
		int maxSd = serverSocket; 				
		// add child sockets to set 
		for (int i = 0; i < maxPlayer; i++) { 
			// socket descriptor 
			int sd = clientSocket[i]; 					
			// if valid socket descriptor then add to read list 
			if (sd > 0) 
				FD_SET(sd, &readfds); 					
			maxSd = max(maxSd, sd); 
		} 
	
		// wait for an activity on one of the sockets, timeout is NULL, so wait indefinitely 
		int activity = select(maxSd + 1, &readfds, NULL, NULL, NULL);

		// If something happened on the master socket, then it's an incoming connection 
		if (FD_ISSET(serverSocket, &readfds)) { 
			sockaddr_in address;	
			int addrlen, newSocket;
			if ((newSocket = accept(serverSocket, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
				puts("Failed to accept connection from client");
				continue;
			}

			bool emptySlotFound = false;
			// add new socket to array of sockets 
			for (int i = 0; i < maxPlayer; i++) {
				// if position is empty 
				if (clientSocket[i] == 0) { 
					emptySlotFound = true;
					clientSocket[i] = newSocket;
					printf("Adding to list of sockets as %d\n" , i);
					// send first message
					const char* message = Message(HEADER_UNAME_REQUEST).c_str();
					if (send(newSocket, message, strlen(message), 0) != strlen(message)) { 
						puts("Failed to send message to client");
					}
					break; 
				}
			}

			// No position is available, reject and close the connection
			if (!emptySlotFound) {
				puts("Server is full");
				const char* message = Message(HEADER_SERVER_FULL).c_str();
				send(newSocket, message, strlen(message), 0);   
				close(newSocket);
			}
		}

		// Else it's some IO operation on some other socket 
		for (int i = 0; i < maxPlayer; i++) {   
			int sd = clientSocket[i];   
						
			if (FD_ISSET(sd, &readfds)) {   
				char clientMessage[MAX_BUFFER+1];
				int valread;
				// Check if it was for closing, and also read the incoming message  
				if ((valread = read(sd, clientMessage, MAX_BUFFER)) == 0) {   
					sockaddr_in address;	
					int addrlen;
					// Somebody disconnected, get his details and print
					getpeername(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
					printf("Host disconnected, ip %s, port %d\n", inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
								
					// Close the socket and mark as 0 in list for reuse  
					close(sd);
					clientSocket[i] = 0;   
				}   							
				// Echo back the message that came in  
				else {   
					// Set the string terminating NULL byte on the end of the data read  
					clientMessage[valread] = 0;
					const char* serverMessage = getServerResponse(i, clientMessage);
					send(sd, serverMessage, strlen(serverMessage), 0);   
				}   
			}   
		}
	}
}
