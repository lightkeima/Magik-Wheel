#ifndef MESSAGETRANSCEIVER_H
#define MESSAGETRANSCEIVER_H

// Code adapted from: https://stackoverflow.com/a/20248772

#include <stdexcept>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

class MessageTransceiver
{
private:
    static ssize_t recv_all(int fd, void* buf, size_t buf_len);

    static ssize_t send_all(int fd, void const* buf, size_t buf_len);

public:
    static bool send_string(int fd, string const& msg);

    static bool recv_string(int fd, string &msg);
};

#endif // MESSAGETRANSCEIVER_H
