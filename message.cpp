#include "message.h"


Message::Message(string header, vector<string> data) {
    this->header = header;
    this->data = data;
}

Message::Message(string buffer) {
    string __tmp(buffer);
    stringstream ss(__tmp);
    string token;
    while (ss >> token) {
        if (header == "")
            header = token;
        else
            data.push_back(token);
    }
}

string Message::str() {
    stringstream ss;
    ss << header;
    for (string token: data)
        ss << " " << token;
    return ss.str();
}