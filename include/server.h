#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "connection.h"
#include <array>
#include <thread>

namespace CliChat 
{

class Server 
{
public:
    Server();
    ~Server();

    std::vector<std::unique_ptr<Connection>> connections;

    int init(int port);
    Connection* accept_connection();
private:
    static constexpr size_t MAX_CONNECTIONS = 100;    
    int server_fd;
    struct sockaddr_in address;
    socklen_t addrlen;

    void run();
    int close_server();
    void handle_client(Connection* conn);
    bool add_connection(std::unique_ptr<Connection> conn);
    bool remove_connection(Connection* conn);
};
}

#endif // SERVER_H