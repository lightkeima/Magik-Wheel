#include "message.h"


Message::Message(string header) {
    this->header = header;
}

Message::Message(string header, vector<string> data) {
    this->header = header;
    this->data = data;
}

Message::Message(char* buffer) {
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

const char* Message::c_str() {
    stringstream ss;
    ss << header;
    for (string token: data)
        ss << " " << token;
    return ss.str().c_str();
}
