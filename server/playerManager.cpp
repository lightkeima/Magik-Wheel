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
        players[playerIdx] = Player();
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

    sort(playerOrder.begin(), playerOrder.end(),
        [&] (int i, int j) {
        return players[i].id < players[j].id;
    }
    );

    reorderByPlayerOrder(players);

    playerIdx = -1;
}

void PlayerManager::disqualify(int playerIdx) {
    players[playerIdx].isInGame = false;
}

int PlayerManager::getNextPlayerIndex() {
    do {
        ++playerIdx;
    } while (!players[playerIdx].isInGame);

    return playerIdx;
}
