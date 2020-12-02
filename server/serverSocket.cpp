#include "serverSocket.h"

ServerSocket::ServerSocket(int maxClient, string dbPath) {	
    this->maxClient = maxClient;
    this->dbPath = dbPath;
    this->playerManager = PlayerManager(maxClient);
    this->gameState = NOT_STARTED;
    this->turnState = 0;
}

void ServerSocket::resetSocket(int maxClient) {
    this->maxClient = maxClient;
    this->playerManager = PlayerManager(maxClient);
    this->gameState = NOT_STARTED;
    this->turnState = 0;
}

void ServerSocket::startGame() {
    playerManager.startGame();

    // sort the player's socket by the playing order (also remove empty socket)
    clientSocket = playerManager.template reorderByPlayerOrder<int>(clientSocket);
    nClient = clientSocket.size();

    // initialize game controller
    gameController = GameController(nClient, Database(dbPath));

    // notify all client that game has started
    // send keyword length and hint to client
    for(int i = 0; i < nClient; ++i) {
        int keywordLength = gameController.getKeyword().length();
        string hint = gameController.getHint();
        string maskedKeyword = gameController.getMaskedKeyword();
        vector<string> data = {to_string(keywordLength), hint, maskedKeyword};
        sendMessageToClient(clientSocket[i], Message(HEADER_GAME_START, data));
    }

    string keyword = gameController.getKeyword();
    printf("Keyword: %s\n", keyword.c_str());

    // update game state
    gameState = ONGOING;

    this->currentPlayerIdx = playerManager.getNextPlayerIndex();

    // Start the first turn
    nextTurn();
}

void ServerSocket::clientResponseHandler(int playerIdx, Message message) {
    cout << "Received message: " << message.str() << endl;

    // client register username
    if (message.header == HEADER_UNAME_RESPONSE) {
        string header;
        vector<string> data;

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

        sendMessageToClient(clientSocket[playerIdx], Message(header, data));
    }
    else if (message.header == HEADER_GUESS_CHAR_RESPONSE) {
        // Check the guess
        char guessChar = message.data[0][0];

        int charGuessResult = gameController.processPlayerAnswer(playerIdx, guessChar);
        if (charGuessResult == 0) {
            currentPlayerIdx = playerManager.getNextPlayerIndex();
            turnState = 0;
        }
        else if (charGuessResult == 1) {
            if (gameController.isAllowToGuessKW()) {
                turnState = 1;
            }
            else {
                turnState = 0;
            }
        }

        // Send result to client
        string header = HEADER_GUESS_CHAR_RESULT;
        vector<string> data = {to_string(charGuessResult)};
        sendMessageToClient(clientSocket[playerIdx], Message(header, data));

        // Notify all clients about the char guess
        header = HEADER_GUESS_CHAR_EVENT;
        data = {playerManager.getPlayerUsername(playerIdx), string(1, guessChar), to_string(charGuessResult)};
        sendMessageToAllClient(Message(header, data));

        if (gameController.isEndGame() || playerManager.allPlayerDisqualified()) {
//            puts("Game finished - Guess char");
            gameState = FINISHED;
        }
        if (gameState == ONGOING) {
            nextTurn();
        }
    }
    else if (message.header == HEADER_GUESS_KEYWORD_RESPONSE) {
        string clientKeyword = (message.data.size() > 0) ? message.data[0] : "";
        int keywordGuessResult = -1;
        // If the player guessed the keyword...
        if (clientKeyword != "") {
            // Check the guess
            keywordGuessResult = gameController.processPlayerAnswer(playerIdx, clientKeyword);

            if (keywordGuessResult == 0) {
                playerManager.disqualify(playerIdx);
                currentPlayerIdx = playerManager.getNextPlayerIndex();
                turnState = 0;
            }
            else if (keywordGuessResult == 1) {
                gameState = FINISHED;
            }

            // Send result to client
            string header = HEADER_GUESS_KEYWORD_RESULT;
            vector<string> data = {to_string(keywordGuessResult)};
            sendMessageToClient(clientSocket[playerIdx], Message(header, data));
        }
        else {
            turnState = 0;
        }

        // Notify all clients about the keyword guess
        string header = HEADER_GUESS_KEYWORD_EVENT;
        vector<string> data = {playerManager.getPlayerUsername(playerIdx), clientKeyword, to_string(keywordGuessResult)};
        sendMessageToAllClient(Message(header, data));

        if (gameController.isEndGame() || playerManager.allPlayerDisqualified()) {
//            puts("Game finished - Guess keyword");
            gameState = FINISHED;
        }
        if (gameState == ONGOING) {
            nextTurn();
        }
    }
    else if (message.header == HEADER_BAD_MESSAGE) {
        exit(1);
    }
    else { // Unknown syntax -> Bad syntax
        string header = HEADER_BAD_MESSAGE;
        vector<string> data = {message.str()};
        sendMessageToClient(clientSocket[playerIdx], Message(header, data));
    }
}

Message ServerSocket::clientConnectedHandler(int clientIdx) {
    return Message(HEADER_UNAME_REQUEST);
}

void ServerSocket::clientDisconnectedHandler(int clientIdx) {
    string username = playerManager.getPlayerUsername(clientIdx);
    printf("%s has left the game\n", username.c_str());
    playerManager.unregisterPlayer(clientIdx);

    // Close the socket and mark as 0 in list for reuse
    close(clientSocket[clientIdx]);
    clientSocket[clientIdx] = 0;

    if (gameController.isEndGame() || playerManager.allPlayerDisqualified()) {
        gameState = FINISHED;
    }

    if (gameState == ONGOING) {
        if (currentPlayerIdx == clientIdx) {
            turnState = 0;
            currentPlayerIdx = playerManager.getNextPlayerIndex();
            nextTurn();
        }
    }
}

bool ServerSocket::sendMessageToClient(int clientSocket, Message message) {
    // Header is empty -> Client have no reponse
    if (message.header == "")
        return true;

    string content = message.str();
    if (!MessageTransceiver::send_string(clientSocket, content)) {
        puts("Failed to send message to client");
        return false;
    }
    return true;
}

bool ServerSocket::sendMessageToAllClient(Message message) {
    bool result = true;
    for(int i = 0; i < nClient; ++i) {
        if (clientSocket[i] != 0) {
            if (!sendMessageToClient(clientSocket[i], message))
                result = false;
        }
    }
    return result;
}

bool ServerSocket::receiveMessageFromClient(int clientSocket, Message &message) {
    puts("Receiving message");
    string content;
    if (!MessageTransceiver::recv_string(clientSocket, content)) {
        return false;
    }
    message = Message(content);
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

void ServerSocket::sendGameResultToAllClient() {
    string keyword = gameController.getKeyword();
    vector<int> playerScore = gameController.getPlayerScore();

    vector<string> gameInfo = {keyword, to_string(nClient)};
    for(int i = 0; i < nClient; ++i) {
        gameInfo.push_back(playerManager.getPlayerUsername(i));
        gameInfo.push_back(to_string(playerScore[i]));
    }

    sendMessageToAllClient(Message(HEADER_GAME_FINISH, gameInfo));
}

void ServerSocket::nextTurn() {
//    puts("nextTurn 1");

    // Sending current game info for all client to render
    string maskedKeyword = gameController.getMaskedKeyword();
//    puts("nextTurn 2");
    string playerTurn = playerManager.getPlayerUsername(currentPlayerIdx);
//    puts("nextTurn 3");
    vector<int> playerScore = gameController.getPlayerScore();
//    puts("nextTurn 4");

//    puts("nextTurn 5");
    vector<string> gameInfo = {maskedKeyword, playerTurn, to_string(nClient)};
    for(int i = 0; i < nClient; ++i) {
        gameInfo.push_back(playerManager.getPlayerUsername(i));
        gameInfo.push_back(to_string(playerScore[i]));
        gameInfo.push_back(to_string(gameController.isDisqualifiedPlayer(i)));
    }

//    puts("nextTurn 6");
    sendMessageToAllClient(Message(HEADER_UPDATE_GAME_INFO, gameInfo));
//    puts("nextTurn 7");

    // Ask current player to guess char or keyword, depend on the turn state
    if (turnState == 0) {
        sendMessageToClient(clientSocket[currentPlayerIdx], Message(HEADER_GUESS_CHAR_REQUEST));
    }
    else {
        sendMessageToClient(clientSocket[currentPlayerIdx], Message(HEADER_GUESS_KEYWORD_REQUEST));
    }

//    puts("nextTurn finished");
}

void ServerSocket::mainLoop() {
    puts("Waiting for players...");

    nClient = maxClient;
    clientSocket.assign(nClient, 0);

    while (true) {
        fd_set readfds;
        // clear the socket set
        FD_ZERO(&readfds);
        // add master socket to set
        FD_SET(serverSocket, &readfds);

        // highest file descriptor number, need it for the select function
        int maxSd = serverSocket;
        // add child sockets to set
        for (int i = 0; i < nClient; i++) {
            // socket descriptor
            int sd = clientSocket[i];
            // if valid socket descriptor then add to read list
            if (sd > 0)
                FD_SET(sd, &readfds);
            maxSd = max(maxSd, sd);
        }

//        puts("Selecting");

        // wait for an activity on one of the sockets, timeout is NULL, so wait indefinitely
        int activity = select(maxSd + 1, &readfds, NULL, NULL, NULL);

//        puts("Selected");

        // If something happened on the master socket, then it's an incoming connection
        if (FD_ISSET(serverSocket, &readfds)) {
            sockaddr_in address;
            int addrlen, newSocket;
            if ((newSocket = accept(serverSocket, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
                puts("Failed to accept connection from client");
                continue;
            }

            // If game already started or finished, new player are not accepted
            if (gameState == ONGOING || gameState == FINISHED) {
                puts("Game already started");
                sendMessageToClient(newSocket, Message(HEADER_GAME_ALREADY_STARTED));
                close(newSocket);
            }
            else {
                // find an empty slot
                int emptySlot = -1;
                for (int i = 0; i < nClient; i++) {
                    if (clientSocket[i] == 0) {
                        emptySlot = i;
                        break;
                    }
                }

                // if an empty slot is found
                if (emptySlot != -1) {
                    printf("Adding to list of sockets as %d\n", emptySlot);
                    clientSocket[emptySlot] = newSocket;
                    sendMessageToClient(newSocket, clientConnectedHandler(emptySlot));
                }
                // Otherwise, reject and close the connection
                else {
                    puts("Server is full");
                    sendMessageToClient(newSocket, Message(HEADER_SERVER_FULL));
                    close(newSocket);
                }
            }
        }
        // Else it's some IO operation on some other socket
        else {
            for (int i = 0; i < nClient; i++) {
                int sd = clientSocket[i];

                if (FD_ISSET(sd, &readfds)) {
                    Message clientMessage;

                    // No content is read -> Client disconnected
                    if (!receiveMessageFromClient(sd, clientMessage)) {
                        clientDisconnectedHandler(i);
                    }
                    else {
                        clientResponseHandler(i, clientMessage);
                    }
                }
            }
        }

        if (gameState == NOT_STARTED) {
            // Check if there's enough player to start the game
            if (playerManager.canStartGame()) {
                startGame();
            }
        }
        else if (gameState == FINISHED) {
            puts("Game finished");
            sendGameResultToAllClient();
            break;
        }
    }
}
