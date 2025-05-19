#ifndef CONNECTION_H
#define CONNECTION_H

#include <sys/socket.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "connection.h"
#include "request.h"
#include <vector>
#include <memory>

namespace CliChat
{

class Connection 
{
private:
    int socket_fd;
    std::vector<char> in_buffer;

public:
    Connection(int socket_fd);
    ~Connection();

    Request* read();
    ssize_t write(const char* data, size_t size);
};

}

#endif // CONNECTION_H