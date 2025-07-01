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
#include <cstdlib>
#include <ctime>
#include <sys/stat.h> // Para mkdir

std::string convertToString(int num) {
    std::ostringstream oss;
    oss << num;
    return oss.str();
}

Server::Server(const ServerConfig& config) : _config(config), _socketFd(-1) {
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
    addr.sin_port = htons(_config.port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(_socketFd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
        throw std::runtime_error("Failed to bind socket");

    if (listen(_socketFd, 10) < 0)
        throw std::runtime_error("Failed to listen on socket");

    fcntl(_socketFd, F_SETFL, O_NONBLOCK);
}

void Server::run() {
    std::cout << "Server running on port " << _config.port << std::endl;
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
                    acceptNewConnection(fds, nfds);
                } else {
                    std::string rawRequest;
                    if (!receiveClientRequest(fds[i].fd, rawRequest)) {
                        closeClientConnection(fds, nfds, i);
                        continue;
                    }

                    handleClientRequest(fds[i].fd, rawRequest);
                    closeClientConnection(fds, nfds, i);
                }
            }
        }
    }
}

void Server::acceptNewConnection(struct pollfd fds[], int& nfds) {
    int clientFd = accept(_socketFd, NULL, NULL);
    if (clientFd >= 0) {
        fcntl(clientFd, F_SETFL, O_NONBLOCK);
        fds[nfds].fd = clientFd;
        fds[nfds].events = POLLIN;
        nfds++;
    }
}

bool Server::receiveClientRequest(int clientFd, std::string& request) {
    char buffer[1024];
    int bytes = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
    if (bytes <= 0)
        return false;

    buffer[bytes] = '\0';
    request = buffer;
    return true;
}

void Server::closeClientConnection(struct pollfd fds[], int& nfds, int i) {
    close(fds[i].fd);
    fds[i] = fds[nfds - 1];
    nfds--;
}

void Server::handleClientRequest(int clientFd, const std::string& rawRequest) {
    Request req(rawRequest);
    std::cout << "[DEBUG] Requisição recebida: " << req.getMethod() << " " << req.getPath() << std::endl;

    std::string path;

    if (req.getPath() == "/" || req.getPath().empty())
        path = _config.root + "/" + _config.index;
    else
        path = _config.root + req.getPath();

    std::cout << "[DEBUG] Caminho final do arquivo: " << path << std::endl;

    if (req.getPath() == "/favicon.ico") {
        sendFavicon(clientFd);
        return;
    }

    if (req.getPath() == "/upload") {
        if (req.getMethod() == "POST") {
            handleUpload(clientFd, rawRequest);
            return;
        } else {
            std::string body = "<html><body><h1>405 Method Not Allowed</h1><a href='/'>Voltar</a></body></html>";
            std::ostringstream res;
            res << "HTTP/1.1 405 Method Not Allowed\r\n"
                << "Content-Type: text/html\r\n"
                << "Content-Length: " << body.length() << "\r\n\r\n"
                << body;
            send(clientFd, res.str().c_str(), res.str().length(), 0);
            shutdown(clientFd, SHUT_WR);
            return;
        }
    }

    std::ifstream file(path.c_str());
    if (!file.is_open()) {
        sendErrorResponse(clientFd, 404);
        return;
    }

    try {
        std::stringstream content;
        content << file.rdbuf();
        std::string body = content.str();

        std::ostringstream response;
        response << "HTTP/1.1 200 OK\r\n"
                 << "Content-Type: " << getMimeType(path) << "\r\n"
                 << "Content-Length: " << body.length() << "\r\n\r\n"
                 << body;

        send(clientFd, response.str().c_str(), response.str().length(), 0);
        shutdown(clientFd, SHUT_WR);
    } catch (...) {
        sendErrorResponse(clientFd, 500);
    }
}

void Server::sendErrorResponse(int clientFd, int code) {
    std::string filepath;

    std::map<int, std::string>::iterator it = _config.error_pages.find(code);
    if (it != _config.error_pages.end())
        filepath = it->second;
    else
        filepath = (code == 404) ? "error_pages/404.html" : "error_pages/500.html";

    std::ifstream file(filepath.c_str());
    std::string body;
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        body = buffer.str();
    } else {
        body = "<html><body><h1>" + convertToString(code) + " Error</h1></body></html>";
    }

    std::ostringstream response;
    response << "HTTP/1.1 " << code
             << (code == 404 ? " Not Found\r\n" : " Internal Server Error\r\n")
             << "Content-Type: text/html\r\n"
             << "Content-Length: " << body.length() << "\r\n\r\n"
             << body;

    send(clientFd, response.str().c_str(), response.str().length(), 0);
    shutdown(clientFd, SHUT_WR); // ✅ Importante
}

void Server::sendFavicon(int clientFd) {
    std::ifstream favFile((_config.root + "/favicon.ico").c_str(), std::ios::binary);
    if (favFile.is_open()) {
        std::ostringstream favBuf;
        favBuf << favFile.rdbuf();
        std::string favData = favBuf.str();

        std::ostringstream res;
        res << "HTTP/1.1 200 OK\r\n"
            << "Content-Type: image/x-icon\r\n"
            << "Content-Length: " << favData.size() << "\r\n\r\n";

        send(clientFd, res.str().c_str(), res.str().length(), 0);
        send(clientFd, favData.c_str(), favData.size(), 0);
    } else {
        sendErrorResponse(clientFd, 404);
    }
}

void Server::handleUpload(int clientFd, const std::string& rawRequest) {
    std::cout << "[DEBUG] Tratando upload POST" << std::endl;

    size_t pos = rawRequest.find("\r\n\r\n");
    if (pos == std::string::npos) {
        std::string response =
            "HTTP/1.1 400 Bad Request\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 12\r\n\r\n"
            "Bad Request\n";
        send(clientFd, response.c_str(), response.length(), 0);
        shutdown(clientFd, SHUT_WR);
        return;
    }

    std::string body = rawRequest.substr(pos + 4);
    std::string value = body;
    size_t posEqual = body.find("=");
    if (posEqual != std::string::npos)
        value = body.substr(posEqual + 1);

    // Cria pasta uploads
    mkdir("uploads", 0755);

    std::ostringstream filename;
    filename << "uploads/mensagem-" << std::time(NULL) << ".txt";

    std::ofstream out(filename.str().c_str());
    if (!out.is_open()) {
        sendErrorResponse(clientFd, 500);
        shutdown(clientFd, SHUT_WR);
        return;
    }

    out << value << "\n";
    out.close();

    std::ostringstream html;
    html << "<html><body>"
         << "<h1>Mensagem recebida com sucesso!</h1>"
         << "<p>Obrigado por enviar: <b>" << value << "</b></p>"
         << "<a href=\"/\">Voltar</a>"
         << "</body></html>";

    std::string bodyHtml = html.str();

    std::ostringstream res;
    res << "HTTP/1.1 200 OK\r\n"
        << "Content-Type: text/html\r\n"
        << "Content-Length: " << bodyHtml.length() << "\r\n\r\n"
        << bodyHtml;

    send(clientFd, res.str().c_str(), res.str().length(), 0);
    shutdown(clientFd, SHUT_WR);

    std::cout << "[DEBUG] Upload salvo: " << value << " em " << filename.str() << std::endl;
}
