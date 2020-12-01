#ifndef MESSAGE_H
#define MESSAGE_H

#define PORT 8888
#define MAX_BUFFER 1024

#define HEADER_UNAME_REQUEST        "USERNAME_REQUEST"
#define HEADER_UNAME_RESPONSE       "USERNAME_RESPONSE"
#define HEADER_UNAME_INVALID        "USERNAME_INVALID"
#define HEADER_UNAME_DUPLICATED     "USERNAME_DUPLICATED"
#define HEADER_REGISTER_SUCCESS     "REGISTER_SUCCESS"
#define HEADER_BAD_MESSAGE          "BAD_MESSAGE"
#define HEADER_SERVER_FULL          "SERVER_FULL"
#define HEADER_GAME_START           "GAME_START"
#define HEADER_GAME_ALREADY_STARTED "GAME_ALREADY_STARTED"
#define HEADER_PLAYER_GUESS         "PLAYER_GUESS"
#define HEADER_RESULT_OF_GUESS      "RESULT_OF_GUESS"

const char DELIM = '|';

#include <bits/stdc++.h>

using namespace std;

struct Message {
    string header;
    vector<string> data;

    Message(string header, vector<string> data);

    Message(string buffer);

    string str();
};

#endif // MESSAGE_H
