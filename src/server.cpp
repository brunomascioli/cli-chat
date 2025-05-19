#include "server.h"

namespace CliChat
{

Server::Server()
    : server_fd(-1), addrlen(sizeof(address)) 
    {
        std::memset(&address, 0, sizeof(address));
}

Server::~Server() 
{
    close_server();
}

int Server::init(int port) 
{
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) 
    {
        std::perror("socket failed");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    addrlen = sizeof(address);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) 
    {
        std::perror("bind failed");
        ::close(server_fd);
        return -1;
    }

    if (listen(server_fd, 3) < 0) 
    {
        std::perror("listen failed");
        ::close(server_fd);
        return -1;
    }

    std::cout << "Server initialized and listening on port " << port << std::endl;

    return 0;
}

int Server::close_server() 
{
    if (server_fd != -1) 
    {
        close(server_fd);
        server_fd = -1;
    }
    return 0;
}

Connection* Server::accept_connection() 
{
    int new_socket;
    if((new_socket = accept(server_fd, (sockaddr*)&address, &addrlen)) == -1)
    {
        perror("Erro em accept");
        return nullptr;
    }

    auto conn = std::make_unique<Connection>(new_socket);

    if (!add_connection(std::move(conn))) 
    {
        ::close(new_socket);
        std::cerr << "Limite de conexões atingido!" << std::endl;
        return nullptr;
    }

    return connections.back().get();
}

bool Server::add_connection(std::unique_ptr<Connection> conn)
{
    if (connections.size() >= MAX_CONNECTIONS)
    {
        return false;
    }
    connections.push_back(std::move(conn));
    return true;
}

}