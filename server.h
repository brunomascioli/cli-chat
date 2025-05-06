#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "connection.h"

class Server 
{
public:
    Server();
    ~Server();

    int init(int port);
    int close_server();
    Connection* accept_connection();
private:
    int server_fd;
    int new_socket;
    struct sockaddr_in address;
    socklen_t addrlen;
    char* in_buffer;
};


#endif // SERVER_H