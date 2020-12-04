#include "messagetransceiver.h"

ssize_t MessageTransceiver::recv_all(int fd, void* buf, size_t buf_len) {
    for(size_t len = buf_len; len;) {
        ssize_t r = ::recv(fd, buf, len, 0);
        if(r <= 0)
            return r;
        buf = static_cast<char*>(buf) + r;
        len -= r;
    }
    return buf_len;
}

ssize_t MessageTransceiver::send_all(int fd, void const* buf, size_t buf_len) {
    for(size_t len = buf_len; len;) {
        ssize_t r = ::send(fd, buf, len, 0);
        if(r <= 0)
            return r;
        buf = static_cast<char const*>(buf) + r;
        len -= r;
    }
    return buf_len;
}

bool MessageTransceiver::send_string(int fd, string const& msg) {
    ssize_t r;
    // Send message length.
    uint32_t len = msg.size();
    len = htonl(len); // In network byte order.
    if((r = send_all(fd, &len, sizeof len)) < 0)
        return false;
    // Send the message.
    if((r = send_all(fd, msg.data(), msg.size())) < 0)
        return false;
    return true;
}

bool MessageTransceiver::recv_string(int fd, string &msg) {
    ssize_t r;
    // Receive message length in network byte order.
    uint32_t len;
    if((r = recv_all(fd, &len, sizeof len)) <= 0)
        return false;
    len = ntohl(len);
    // Receive the message.
    msg = string(len, '\0');
    if(len && (r = recv_all(fd, &msg[0], len)) <= 0)
        return false;
    return true;
}
