#ifndef MESSAGE_H
#define MESSAGE_H

#define PORT 8888
#define MAX_BUFFER 1024

#define HEADER_UNAME_REQUEST          "USERNAME_REQUEST"
#define HEADER_UNAME_RESPONSE         "USERNAME_RESPONSE"
#define HEADER_UNAME_INVALID          "USERNAME_INVALID"
#define HEADER_UNAME_DUPLICATED       "USERNAME_DUPLICATED"
#define HEADER_REGISTER_SUCCESS       "REGISTER_SUCCESS"
#define HEADER_BAD_MESSAGE            "BAD_MESSAGE"
#define HEADER_SERVER_FULL            "SERVER_FULL"
#define HEADER_GAME_START             "GAME_START"
#define HEADER_GAME_ALREADY_STARTED   "GAME_ALREADY_STARTED"
#define HEADER_GUESS_CHAR_REQUEST     "GUESS_CHAR_REQUEST"
#define HEADER_GUESS_CHAR_RESPONSE    "GUESS_CHAR_RESPONSE"
#define HEADER_GUESS_CHAR_RESULT      "GUESS_CHAR_RESULT"
#define HEADER_GUESS_KEYWORD_REQUEST  "GUESS_KEYWORD_REQUEST"
#define HEADER_GUESS_KEYWORD_RESPONSE "GUESS_KEYWORD_RESPONSE"
#define HEADER_GUESS_KEYWORD_RESULT   "GUESS_KEYWORD_RESULT"
#define HEADER_UPDATE_GAME_INFO       "UPDATE_GAME_INFO"

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
