#include "connection.h"

Connection::Connection(int socket_fd) : socket_fd(socket_fd)
{
}

Connection::~Connection() {
    delete[] in_buffer; 
    close(socket_fd);
}

ssize_t Connection::read() {

}

ssize_t Connection::write(const char* data, size_t size) {

}