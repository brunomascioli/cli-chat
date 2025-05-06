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

class Connection 
{
private:
    int socket_fd;
    char* in_buffer;

public:
    Connection(int socket_fd);
    ~Connection();

    ssize_t read();
    ssize_t write(const char* data, size_t size);
};

#endif // CONNECTION_H