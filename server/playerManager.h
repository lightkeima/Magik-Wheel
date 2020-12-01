#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <bits/stdc++.h>

using namespace std;

enum GameState {
    NOT_STARTED,
    ONGOING,
    FINISHED
};

struct Player {
    int id;
    bool isInGame;
    string username;

    Player();
};

class PlayerManager {
private:
    int maxPlayer;

    vector<Player> players;

    int currentID;

    vector<int> playerOrder;

    int playerIdx;

public:
    PlayerManager();

    PlayerManager(int maxPlayer);

    string getPlayerUsername(int playerIdx);

    bool isValidUsername(string username);

    bool isDuplicatedUsername(string username);

    void registerPlayer(int playerIdx, string username);

    void unregisterPlayer(int playerIdx);

    template<class T>
    vector<T> reorderByPlayerOrder(vector<T> objVec);

    void startGame();

    int getNextPlayerIndex();
};

#endif // PLAYERMANAGER_H
