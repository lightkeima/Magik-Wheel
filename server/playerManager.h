#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <bits/stdc++.h>

using namespace std;

struct Player {
    // player id (player who register earlier will have lower id)
    int id;
    bool isInGame;
    string username;

    Player();
};

class PlayerManager {
private:
    // maximum number of player
    int maxPlayer;

    vector<Player> players;

    // keep track of the next id to give to player
    int currentID;

    // the registration order of the player who is still registered
    vector<int> playerOrder;

    // index of the player that play the current turn
    int playerIdx;

    // number of currently registered player
    int nPlayer;

public:
    PlayerManager();

    PlayerManager(int maxPlayer);

    string getPlayerUsername(int playerIdx);

    bool isValidUsername(string username);

    bool isDuplicatedUsername(string username);

    void registerPlayer(int playerIdx, string username);

    void unregisterPlayer(int playerIdx);

    bool canStartGame();

    void startGame();

    int getNextPlayerIndex();

    template<class T>
    vector<T> reorderByPlayerOrder(vector<T> objVec) {
        vector<T> result(playerOrder.size());
        for(int i = 0; i < playerOrder.size(); ++i)
            result[i] = objVec[playerOrder[i]];
        return result;
    }

    void disqualify(int playerIdx);
};

#endif // PLAYERMANAGER_H
