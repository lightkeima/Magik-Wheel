#include "gamecontroller.h"

// The player order should be controlled by the Server
// The game logic will tells the server whether the player is disqualified or not

GameController::GameController() {

}

GameController::GameController(int N, Database database) {
    this->MAX_TURN = 2*N;
    this->START_GUESSING_KW_TURN = N+1;
    this->numPlayers = N;
    this->currentTurn = 1;
    this->consecutiveIncorrectGuess = 0;
    this->playerScore.assign(N, 0);
    this->isDisqualified.assign(N, false);
    this->kwDatabase = database;
    this->kwGuessed = false;
    this->chooseRandomKeyword();
}

void GameController::checkGuessChar(char c) {
    this->latestCorrectCharGuessPos.clear();

    for (int i = 0; i < (int) this->keyword.length(); i++) {
        if (this->keyword[i] == c)
            this->latestCorrectCharGuessPos.push_back(i);
    }

}

int GameController::processPlayerAnswer(int playerIdx, char guessChar) {

    if (!this->validPlayerIdx(playerIdx) || isDisqualifiedPlayer(playerIdx)) {
        return -1;
    }


    int status;

    // Check the answer
    this->checkGuessChar(guessChar);

    if (latestCorrectCharGuessPos.size() != 0)
        status = 1;
    else
        status  = 0;

    // Update the score
    if (status) {
        // Correct guess:  +1 point
        this->playerScore[playerIdx] += 1;

        // Update the mask
        for (auto pos : latestCorrectCharGuessPos)
            masked[pos] = false;

        consecutiveIncorrectGuess = 0;
    } else {
        consecutiveIncorrectGuess += 1;
    }

    currentTurn += 1;

    // return the corresponding code
    return status;
}

void GameController::restart() {


    // Restart player
    playerScore.assign(this->numPlayers, 0);
    isDisqualified.assign(this->numPlayers, false);

    consecutiveIncorrectGuess = 0;
    currentTurn = 1;
    kwGuessed = false;

    // Choose new keyword
    this->chooseRandomKeyword();


}

int GameController::processPlayerAnswer(int playerIdx, string guessKw) {
    // Check keyword
    if (!this->validPlayerIdx(playerIdx) || isDisqualifiedPlayer(playerIdx) || !isAllowToGuessKW()) {
        return -1;
    }


    int status;

    if (guessKw == this->keyword)
        status = 1;
    else
        status = 0;

    if (status) {
        // 5 points for correct keyword
        this->playerScore[playerIdx] += 5;

        // Update the status of the game
        this->kwGuessed = true;
    } else{
        // Disqualifed the player for wrong keyword guess
        this->isDisqualified[playerIdx]  = true;
    }


    return status;
}

bool GameController::isAllowToGuessKW() {
    return this->currentTurn > this->START_GUESSING_KW_TURN;
}

pair<string, string> GameController::chooseRandomKeyword() {

    auto kwHint = this->kwDatabase.getKeyword(-1);
    this->keyword = kwHint.first;
    this->hint = kwHint.second;

    // Update the size of the mask
    // Initially the keyword is masked
    this->masked.assign(this->keyword.length(), true);
    this->latestCorrectCharGuessPos.clear();

    return kwHint;
}


string GameController::getKeyword() {
    return this->keyword;
}

string GameController::getHint() {
    return this->hint;
}

vector<bool> GameController::getMask() {
    return this->masked;
}

vector<int> GameController::getPlayerScore() {
    return this->playerScore;
}

bool GameController::validPlayerIdx(int idx) {
    return 0 <= idx && idx < this->numPlayers;
}

bool GameController::isDisqualifiedPlayer(int idx) {
    return this->isDisqualified[idx];
}

bool GameController::isEndGame() {
    return this->kwGuessed || this->consecutiveIncorrectGuess >= this->MAX_TURN;
}

string GameController::getMaskedKeyword() {
    string maskedKeyword;

    for (int i = 0; i < (int) this->keyword.length(); i++) {
        if (this->masked[i])
            maskedKeyword += '*';
        else
            maskedKeyword += this->keyword[i];
    }

    return maskedKeyword;
}

vector<int> GameController::getCorrectCharGuessPosition() {
    return this->latestCorrectCharGuessPos;
}



