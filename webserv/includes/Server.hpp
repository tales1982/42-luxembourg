// Server.hpp
#ifndef SERVER_HPP
#define SERVER_HPP

#include "Config.hpp"
#include <vector>
#include <map>

class Server {
public:
    Server(const Config& config);
    void run();

private:
    Config _config;
    int _socketFd;
    void setupSocket();
    void handleConnections();
};

#endif