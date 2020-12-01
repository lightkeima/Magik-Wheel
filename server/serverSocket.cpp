#include "serverSocket.h"

ServerSocket::ServerSocket(int maxClient, string dbPath) {	
	this->maxClient = maxClient;
	this->dbPath = dbPath;
    this->playerManager = PlayerManager(maxClient);
}

void ServerSocket::startGame() {
	
}

Message ServerSocket::clientResponseHandler(int playerIdx, Message message) {
    cout << "Received message: " << message.str() << endl;

    string header;
	vector<string> data;

    if (message.header == HEADER_UNAME_RESPONSE) {
        if (message.data.size() != 1) { // Bad syntax
            header = HEADER_BAD_MESSAGE;
        }
        else {
            string username = message.data[0];
            if (!playerManager.isValidUsername(username)) {
                header = HEADER_UNAME_INVALID;
            }
            else if (playerManager.isDuplicatedUsername(username)) {
                header = HEADER_UNAME_DUPLICATED;
                data = {username};
            }
            else {
                printf("Welcome to the game, %s!\n", username.c_str());
                playerManager.registerPlayer(playerIdx, username);
                header = HEADER_REGISTER_SUCCESS;
            }
        }
    }
    else if (message.header == HEADER_BAD_MESSAGE) {
        cout << message.str() << endl;
        puts("Something wrong I can feel it...");
        exit(1);
    }
	else { // Unknown syntax -> Bad syntax
		header = HEADER_BAD_MESSAGE;
	}

    return Message(header, data);
}

Message ServerSocket::clientConnectedHandler(int clientIdx) {
	return Message(HEADER_UNAME_REQUEST);
}

void ServerSocket::clientDisconnectedHandler(int clientIdx) {
	string username = playerManager.getPlayerUsername(clientIdx);
	printf("%s has left the game\n", username.c_str());
	playerManager.unregisterPlayer(clientIdx);
}

bool ServerSocket::sendMessageToClient(int socket, Message message) {
    // Header is empty -> Client have no reponse
    if (message.header == "")
        return true;
    string __message = message.str();
    // Otherwise, send the message normally
    const char* buffer = __message.c_str();
    if (send(socket, buffer, strlen(buffer), 0) != strlen(buffer)) {
        puts("Failed to send message to client");
        return false;
    }
    return true;
}

bool ServerSocket::initSocket() {
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

void ServerSocket::mainLoop() {
	puts("Waiting for players...");

	clientSocket.assign(maxClient, 0);
	
	while (true) {
		fd_set readfds; 
		// clear the socket set 
		FD_ZERO(&readfds);
		// add master socket to set 
		FD_SET(serverSocket, &readfds);
		
		// highest file descriptor number, need it for the select function 
		int maxSd = serverSocket; 				
		// add child sockets to set 
		for (int i = 0; i < maxClient; i++) { 
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
			for (int i = 0; i < maxClient; i++) {
				// if position is empty 
				if (clientSocket[i] == 0) { 
					emptySlotFound = true;
					clientSocket[i] = newSocket;
					printf("Adding to list of sockets as %d\n", i);
					sendMessageToClient(newSocket, clientConnectedHandler(i));
					break; 
				}
			}

			// No position is available, reject and close the connection
			if (!emptySlotFound) {
				puts("Server is full");
				sendMessageToClient(newSocket, Message(HEADER_SERVER_FULL));
				close(newSocket);
			}
		}

		// Else it's some IO operation on some other socket 
		for (int i = 0; i < maxClient; i++) {   
			int sd = clientSocket[i];   
						
			if (FD_ISSET(sd, &readfds)) {   
				char clientMessage[MAX_BUFFER+1];
				int valread;
				// Check if it was for closing, and also read the incoming message  
				if ((valread = read(sd, clientMessage, MAX_BUFFER)) == 0) {   
					clientDisconnectedHandler(i);
					// Close the socket and mark as 0 in list for reuse  
					close(sd);
					clientSocket[i] = 0;
				}   							
				else {   
					// Set the string terminating NULL byte on the end of the data read  
					clientMessage[valread] = 0;
					Message serverMessage = clientResponseHandler(i, string(clientMessage));
					sendMessageToClient(clientSocket[i], serverMessage);
				}
			}
		}
	}
}
