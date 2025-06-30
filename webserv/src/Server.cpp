// Server.cpp
#include "Server.hpp"
#include "Request.hpp"
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <cstring>
#include <ctime>

Server::Server(const Config& config) : _config(config), _socketFd(-1) {
    setupSocket();
}

void Server::setupSocket() {
    _socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (_socketFd < 0)
        throw std::runtime_error("Failed to create socket");

    int opt = 1;
    setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_config.getPort());
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(_socketFd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
        throw std::runtime_error("Failed to bind socket");

    if (listen(_socketFd, 10) < 0)
        throw std::runtime_error("Failed to listen on socket");

    fcntl(_socketFd, F_SETFL, O_NONBLOCK);
}

void Server::run() {
    std::cout << "Server running on port " << _config.getPort() << std::endl;
    handleConnections();
}

void Server::handleConnections() {
    struct pollfd fds[1024];
    int nfds = 1;
    fds[0].fd = _socketFd;
    fds[0].events = POLLIN;

    while (true) {
        int ret = poll(fds, nfds, -1);
        if (ret < 0) {
            perror("poll");
            continue;
        }

        for (int i = 0; i < nfds; ++i) {
            if (fds[i].revents & POLLIN) {
                if (fds[i].fd == _socketFd) {
                    int clientFd = accept(_socketFd, NULL, NULL);
                    if (clientFd >= 0) {
                        fcntl(clientFd, F_SETFL, O_NONBLOCK);
                        fds[nfds].fd = clientFd;
                        fds[nfds].events = POLLIN;
                        nfds++;
                    }
                } else {
                    char buffer[4096];
                    int bytes = recv(fds[i].fd, buffer, sizeof(buffer) - 1, 0);
                    if (bytes <= 0) {
                        close(fds[i].fd);
                        fds[i] = fds[nfds - 1];
                        nfds--;
                        i--;
                    } else {
                        buffer[bytes] = '\0';
                        std::string rawRequest(buffer);
                        Request req(rawRequest);

                        std::cout << "Method: " << req.getMethod() << std::endl;
                        std::cout << "Path: " << req.getPath() << std::endl;
                        std::cout << "Version: " << req.getVersion() << std::endl;

                        std::string method = req.getMethod();
                        std::string path = "www" + req.getPath();
                        if (path == "www/")
                            path = "www/index.html";

                        if (method == "POST") {
                            std::ofstream out("uploads/data.txt", std::ios::app);
                            if (out.is_open()) {
                                out << rawRequest << "\n";
                                out.close();

                                std::string msg = "Upload realizado!";
                                std::ostringstream response;
                                response << "HTTP/1.1 201 Created\r\n"
                                         << "Content-Type: text/plain\r\n"
                                         << "Content-Length: " << msg.length() << "\r\n\r\n"
                                         << msg;
                                std::string resStr = response.str();
                                send(fds[i].fd, resStr.c_str(), resStr.length(), 0);
                            } else {
                                std::string err = "<html><body><h1>500 Internal Server Error</h1></body></html>";
                                std::ostringstream response;
                                response << "HTTP/1.1 500 Internal Server Error\r\n"
                                         << "Content-Type: text/html\r\n"
                                         << "Content-Length: " << err.length() << "\r\n\r\n"
                                         << err;
                                std::string resStr = response.str();
                                send(fds[i].fd, resStr.c_str(), resStr.length(), 0);
                            }
                        } else {
                            std::ifstream file(path.c_str());
                            if (!file.is_open()) {
                                std::ifstream errorFile("error_pages/404.html");
                                std::string errorBody;
                                if (errorFile.is_open()) {
                                    std::stringstream buffer;
                                    buffer << errorFile.rdbuf();
                                    errorBody = buffer.str();
                                } else {
                                    errorBody = "<html><body><h1>404 Not Found</h1></body></html>";
                                }
                                std::ostringstream response;
                                response << "HTTP/1.1 404 Not Found\r\n"
                                         << "Content-Type: " << getMimeType(path) << "\r\n"
                                         << "Content-Length: " << errorBody.length() << "\r\n\r\n"
                                         << errorBody;
                                std::string resStr = response.str();
                                send(fds[i].fd, resStr.c_str(), resStr.length(), 0);
                            } else {
                                try {
                                    std::stringstream content;
                                    content << file.rdbuf();
                                    std::string body = content.str();
                                    std::ostringstream response;
                                    response << "HTTP/1.1 200 OK\r\n"
                                             << "Content-Type: " << getMimeType(path) << "\r\n"
                                             << "Content-Length: " << body.length() << "\r\n\r\n"
                                             << body;
                                    std::string resStr = response.str();
                                    send(fds[i].fd, resStr.c_str(), resStr.length(), 0);
                                } catch (...) {
                                    std::ifstream errorFile("error_pages/500.html");
                                    std::string errorBody;
                                    if (errorFile.is_open()) {
                                        std::stringstream buffer;
                                        buffer << errorFile.rdbuf();
                                        errorBody = buffer.str();
                                    } else {
                                        errorBody = "<html><body><h1>500 Internal Server Error</h1></body></html>";
                                    }
                                    std::ostringstream response;
                                    response << "HTTP/1.1 500 Internal Server Error\r\n"
                                             << "Content-Type: " << getMimeType(path) << "\r\n"
                                             << "Content-Length: " << errorBody.length() << "\r\n\r\n"
                                             << errorBody;
                                    std::string resStr = response.str();
                                    send(fds[i].fd, resStr.c_str(), resStr.length(), 0);
                                }
                            }
                        }

                        close(fds[i].fd);
                        fds[i] = fds[nfds - 1];
                        nfds--;
                        i--;
                    }
                }
            }
        }
    }
}