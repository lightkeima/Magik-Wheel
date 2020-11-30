#ifndef MESSAGE_H
#define MESSAGE_H

#define PORT 8888
#define MAX_BUFFER 1024

#define HEADER_UNAME_REQUEST    "USERNAME_REQUEST"
#define HEADER_UNAME_RESPONSE   "USERNAME_RESPONSE"
#define HEADER_UNAME_INVALID    "USERNAME_INVALID"
#define HEADER_UNAME_DUPLICATED "USERNAME_DUPLICATED"
#define HEADER_REGISTER_SUCCESS "REGISTER_SUCCESS"
#define HEADER_BAD_MESSAGE      "BAD_MESSAGE"
#define HEADER_SERVER_FULL      "SERVER_FULL"

#include <bits/stdc++.h>

using namespace std;

struct Message {
	string header;
	vector<string> data;

	Message(string header);

	Message(string header, vector<string> data);

	Message(char* buffer);

	const char* c_str();
};

#endif // MESSAGE_H
