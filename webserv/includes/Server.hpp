// Server.hpp
#ifndef SERVER_HPP
#define SERVER_HPP

#include "Config.hpp"
#include <string>

class Server {
public:
    Server(const ServerConfig& config);
    void run();

private:
    ServerConfig _config;
    int _socketFd;

    
    void setupSocket();
    void handleConnections();
    void acceptNewConnection(struct pollfd fds[], int& nfds);
    bool receiveClientRequest(int clientFd, std::string& request);
    void closeClientConnection(struct pollfd fds[], int& nfds, int i);
    void handleClientRequest(int clientFd, const std::string& rawRequest);
    void sendErrorResponse(int clientFd, int code);
    void sendFavicon(int clientFd);
    void handleUpload(int clientFd, const std::string& rawRequest);
    
};

#endif
