#include "connection.h"

namespace CliChat 
{

Connection::Connection(int socket_fd) 
    : socket_fd(socket_fd), in_buffer(1024) 
{
}

Connection::~Connection() 
{
    if(socket_fd != -1) 
    {
        close(socket_fd);
    }
}

std::unique_ptr<Request> Connection::receive_data() 
{
    ssize_t res = read(socket_fd, in_buffer.data(), in_buffer.size());
    
    if (res < 0) 
    {
        std::cerr << "Error reading data" << std::endl;
        return nullptr;
    }

    if (res == 0) 
    {
        std::cerr << "Connection closed by peer" << std::endl;
        return nullptr;
    }

    std::string payload(in_buffer.data(), res);

    return std::make_unique<Request>(std::move(payload));
}

ssize_t Connection::send_data(std::string_view data) 
{

    ssize_t total_written = 0;
    const char* buffer = data.data();
    size_t size = data.size();

    while (total_written < static_cast<ssize_t>(size)) 
    {
        ssize_t written = write(socket_fd, buffer + total_written,size - total_written);
        
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