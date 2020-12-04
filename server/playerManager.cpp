#include "playerManager.h"

Player::Player() {
    username = "";
    isInGame = false;
    id = -1;
}

PlayerManager::PlayerManager() {}

PlayerManager::PlayerManager(int maxPlayer) {
    this->maxPlayer = maxPlayer;
    this->nPlayer = 0;
    this->players.assign(maxPlayer, Player());
}

string PlayerManager::getPlayerUsername(int playerIdx) {
    return players[playerIdx].username;
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
            return true;
    }
    return false;
}

void PlayerManager::registerPlayer(int playerIdx, string username) {
    if (players[playerIdx].id == -1) {
        ++nPlayer;
        players[playerIdx].id = ++currentID;
        players[playerIdx].isInGame = false;
        players[playerIdx].username = username;
    }
}

void PlayerManager::unregisterPlayer(int playerIdx) {
    if (players[playerIdx].id != -1) {
        players[playerIdx].id = -1;
        players[playerIdx].isInGame = false;
        --nPlayer;
    }
}

bool PlayerManager::canStartGame() {
    return nPlayer == maxPlayer;
}

void PlayerManager::startGame() {
    playerOrder.clear();

    for(int i = 0; i < maxPlayer; ++i) {
        if (players[i].id != -1) {
            players[i].isInGame = true;
            playerOrder.push_back(i);
        }
    }

//    for(int i = 0; i < maxPlayer; ++i) {
//        printf("%s %d\n", players[i].username.c_str(), players[i].id);
//    }

    sort(playerOrder.begin(), playerOrder.end(),
        [&] (int i, int j) {
        return players[i].id < players[j].id;
    }
    );

//    for(int x: playerOrder)
//        printf("%d ", x);
//    puts("");

    players = reorderByPlayerOrder(players);

    playerIdx = -1;
}

bool PlayerManager::allPlayerDisqualified() {
    return nPlayer == 0;
}

void PlayerManager::disqualify(int playerIdx) {
    players[playerIdx].isInGame = false;
}

int PlayerManager::getNextPlayerIndex() {
    do {
        playerIdx = (playerIdx + 1) % players.size();
    } while (!players[playerIdx].isInGame);

    return playerIdx;
}
