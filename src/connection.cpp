#include "connection.h"

namespace CliChat 
{

Connection::Connection(int socket_fd) 
    : socket_fd(socket_fd), in_buffer(1024) 
{
}

Connection::~Connection() 
{
    close(socket_fd);
}

Request* Connection::read() 
{
    ssize_t res = ::read(socket_fd, in_buffer.data(), in_buffer.size());
    
    if (res < 0) 
    {
        std::cerr << "Error reading data" << std::endl;
        return nullptr;
    }

    std::cout << "Payload recebido: " << std::string(in_buffer.data(), res) << std::endl;        

    auto req = new Request(std::string(in_buffer.data(), res));
    return req;
}

ssize_t Connection::write(const char* data, size_t size) 
{
    ssize_t total_written = 0;
    while (total_written < static_cast<ssize_t>(size)) 
    {
        ssize_t written = ::write(
            socket_fd, 
            data + total_written,
            size - total_written
        );
        
        if(written <= 0) 
        {
            std::cerr << "Error writing data" << std::endl;
            return -1;
        }

        total_written += written;
    
    }
    
    return total_written;
}

}