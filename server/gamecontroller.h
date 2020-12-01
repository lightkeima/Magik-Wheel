#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <bits/stdc++.h>
#include "database.h"

using namespace std;


class GameController
{
private:
    const int MAX_TURN = 5;
    const int START_GUESSING_KW_TURN = 2;

    int numPlayers;
    vector<int> playerScore;
    vector<bool> isDisqualified;


    Database kwDatabase;
    string keyword;
    string hint;
    vector<bool> masked;
    vector<int> latestCorrectCharGuessPos;

    int currentTurn = 0;
    bool kwGuessed = false; // Is keyword guessed correctly?


    pair<string, string> chooseRandomKeyword();
    void checkGuessChar(char c);
    bool validPlayerIdx(int idx);

    


public:
    GameController();

    GameController(int N, Database database);


    void restart();

    /**
     * @brief processPlayerAnswer: Check the player's character guess and update the score.
     * @param playerIdx
     * @param guessChar
     * @return
     *      -1 for invalid guess. This happens when they player is disqualied or the playerIdx is invalid
     *       0 for incorrect guess
     *       1 for correct guess
     */
    int processPlayerAnswer(int playerIdx, char guessChar);

    /**
     * @brief processPlayerAnswer: check the player's keyword guess, update the score and disqualify the player if neccessary.
     * @param playerIdx
     * @param kw
     * @return
     *      -1 for invalid guess. This happens when they player is disqualied or the playerIdx is invalid or it's not the turn to get keyword yet
     *       0 for incorrect guess
     *       1 for correct guess
     */
    int processPlayerAnswer(int playerIdx, string kw);


    /**
     * @brief getCorrectCharGuessPosition: return the correct char guess indices (0-index) in the string keyword.
     *      This function should be called after `processPlayerAnswer()` otherwise it returns the result for latest player's guess
     * @return vector contains correctly guess characters. When there's not correct guess, return empty vector
     */
    vector<int> getCorrectCharGuessPosition();

    string getKeyword();

    string getHint();


    vector<bool> getMask();

    vector<int> getPlayerScore();

    /**
     * @brief getMaskedKeyword: Get keyword's representation with only correctly guessed characters are displayed and others are replaced by a '*' character
     * @return string - maskedKeyword
     */
    string getMaskedKeyword();

    bool isAllowToGuessKW();

    /**
     * @brief isEndGame: Check whether the game ends or not. Please refer to the game rules for the ending condition
     * @return true if endgame, otherwise false
     */
    bool isEndGame();

    bool isDisqualifiedPlayer(int idx);


};

#endif // GAMECONTROLLER_H
