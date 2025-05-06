#include "server.h"

Server::Server()
    : server_fd(-1), new_socket(-1), addrlen(sizeof(address)), in_buffer(nullptr) {
        std::memset(&address, 0, sizeof(address));
}

Server::~Server() {
    close_server();
    if(in_buffer) {
        delete[] in_buffer;
        in_buffer = nullptr;
    }
}

int Server::init(int port) {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::perror("socket failed");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    addrlen = sizeof(address);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::perror("bind failed");
        ::close(server_fd);
        return -1;
    }

    if (listen(server_fd, 3) < 0) {
        std::perror("listen failed");
        ::close(server_fd);
        return -1;
    }

    std::cout << "Server initialized and listening on port " << port << std::endl;

    return 0;
}

int Server::close_server() {
    if (server_fd != -1) {
        close(server_fd);
        server_fd = -1;
    }
    if(new_socket != -1) {
        close(new_socket);
        new_socket = -1;
    }
    return 0;
}

Connection* Server::accept_connection() {
    if((new_socket = accept(server_fd, (sockaddr*)&address, &addrlen)) == -1) {
        perror("Erro em accept");
    }
    Connection* conn = new Connection(new_socket);
    return conn;
}