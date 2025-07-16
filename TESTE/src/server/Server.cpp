// src/server/Server.cpp
#include "../../include/server/Server.hpp"
#include "../../include/server/RequestHandler.hpp"
#include "../../include/server/ResponseBuilder.hpp"
#include <fstream>     // std::ofstream
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <cerrno>
#include <cstring>

// Extrai boundary dos headers HTTP (case-insensitive)
static std::string extract_boundary(const std::string &headers) {
    std::string lower = headers;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    size_t bpos = lower.find("boundary=");
    if (bpos == std::string::npos) return "";
    bpos += 9; // pular "boundary="
    size_t end = lower.find_first_of(";\r\n ", bpos);
    if (end == std::string::npos) end = lower.size();
    std::string token = headers.substr(bpos, end - bpos);
    return "--" + token;
}

int ft_server(const ServerConfig &config) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Socket error: " << strerror(errno) << std::endl;
        return 1;
    }
    fcntl(server_fd, F_SETFL, O_NONBLOCK);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = inet_addr(config.host.c_str());
    addr.sin_port        = htons(config.port);

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0 ||
        listen(server_fd, 10) < 0) {
        std::cerr << "Bind/Listen error: " << strerror(errno) << std::endl;
        return 1;
    }

    fd_set master, readset;
    FD_ZERO(&master);
    FD_SET(server_fd, &master);
    int max_fd = server_fd;

    std::cout << "Server listening on " << config.host << ":" << config.port << std::endl;

    while (true) {
        readset = master;
        if (select(max_fd + 1, &readset, NULL, NULL, NULL) < 0) {
            std::cerr << "Select error: " << strerror(errno) << std::endl;
            break;
        }

        // Aceita novas conexões
        if (FD_ISSET(server_fd, &readset)) {
            int client = accept(server_fd, NULL, NULL);
            if (client >= 0) {
                fcntl(client, F_SETFL, O_NONBLOCK);
                FD_SET(client, &master);
                if (client > max_fd) max_fd = client;
                std::cout << "New client FD=" << client << std::endl;
            } else {
                std::cerr << "Accept error: " << strerror(errno) << std::endl;
            }
        }

        // Trata cada socket pronto
        for (int fd = server_fd + 1; fd <= max_fd; ++fd) {
            if (!FD_ISSET(fd, &readset)) continue;

            // Lê headers + parte do body
            std::string request;
            char buf[8192];
            int n = read(fd, buf, sizeof(buf));
            if (n <= 0) {
                close(fd);
                FD_CLR(fd, &master);
                continue;
            }
            request.append(buf, n);

            // Separa headers e body parcial
            size_t sep = request.find("\r\n\r\n");
            if (sep == std::string::npos) continue; // aguarda mais dados
            std::string headers = request.substr(0, sep);
            std::string body    = request.substr(sep + 4);

            // Extrai Content-Length
            size_t content_length = 0;
            size_t clp = headers.find("Content-Length:");
            if (clp != std::string::npos) {
                std::istringstream is(headers.substr(clp + 15));
                is >> content_length;
            }
            // Lê o resto do body
            while (body.size() < content_length) {
                int m = read(fd, buf, sizeof(buf));
                if (m <= 0) break;
                body.append(buf, m);
            }

            // Debug headers
            std::cout << "\n--- HEADERS (FD=" << fd << ") ---\n"
                      << headers << "\n";

            // Parse método e caminho
            std::istringstream ls(headers);
            std::string method, path;
            ls >> method >> path;
            std::cout << "Method=" << method << " Path=" << path << std::endl;

            // Upload multipart
            if (method == "POST" && path == "/upload") {
                // DEBUG: imprime prefixo do body
                std::cout << "--- BODY PREFIX (FD=" << fd << ") ---\n"
                          << body.substr(0, std::min<size_t>(body.size(), 256))
                          << "\n---------------------\n";

                std::string boundary = extract_boundary(headers);
                std::string filename;
                std::string file_content;

                // Extrai filename
                size_t fpos = body.find("filename=\"");
                if (fpos != std::string::npos) {
                    fpos += 10;
                    size_t fend = body.find('\"', fpos);
                    filename = body.substr(fpos, fend - fpos);
                }
                // Extrai conteúdo
                size_t start = body.find("\r\n\r\n", fpos);
                if (start != std::string::npos) {
                    start += 4;
                    size_t end = body.find(boundary, start);
                    if (end != std::string::npos) {
                        file_content = body.substr(start, end - start - 2);
                    }
                }
                std::cout << "Boundary='" << boundary
                          << "' filename='" << filename
                          << "' contentSize=" << file_content.size()
                          << std::endl;

                if (boundary.empty() || filename.empty() || file_content.empty()) {
                    std::cerr << "Invalid multipart: 400" << std::endl;
                    std::string err = read_file(config.error_500);
                    std::ostringstream resp;
                    resp << "HTTP/1.1 400 Bad Request\r\n"
                         << "Content-Type: text/html\r\n"
                         << "Content-Length: " << err.size() << "\r\n\r\n"
                         << err;
                    write(fd, resp.str().c_str(), resp.str().size());
                } else {
                    std::string dir = get_upload_dir_by_extension(filename);
                    std::ofstream out((dir + filename).c_str(), std::ios::binary);
                    out.write(file_content.c_str(), file_content.size());
                    out.close();
                    std::cout << "Saved to '" << dir + filename << "'" << std::endl;

                    std::string ok = read_file("www/upload_success.html");
                    std::ostringstream resp;
                    resp << "HTTP/1.1 200 OK\r\n"
                         << "Content-Type: text/html\r\n"
                         << "Content-Length: " << ok.size() << "\r\n\r\n"
                         << ok;
                    write(fd, resp.str().c_str(), resp.str().size());
                }
                close(fd);
                FD_CLR(fd, &master);
                continue;
            }

            // Servir estáticos / autoindex
            if (path == "/") path = "/index.html";
            if (path == "/all-uploads") {
                std::string page = generate_all_uploads_page();
                std::ostringstream resp;
                resp << "HTTP/1.1 200 OK\r\n"
                     << "Content-Type: text/html\r\n"
                     << "Content-Length: " << page.size() << "\r\n\r\n"
                     << page;
                write(fd, resp.str().c_str(), resp.str().size());
                continue;
            }

            // Servir arquivo
            std::string full = config.root + path;
            std::string data = read_file(full);
            std::ostringstream resp;
            if (data.empty()) {
                std::string err = read_file(config.error_404);
                resp << "HTTP/1.1 404 Not Found\r\n"
                     << "Content-Type: text/html\r\n"
                     << "Content-Length: " << err.size() << "\r\n\r\n"
                     << err;
            } else {
                resp << "HTTP/1.1 200 OK\r\n"
                     << "Content-Type: " << get_mime_type(full) << "\r\n"
                     << "Content-Length: " << data.size() << "\r\n\r\n"
                     << data;
            }
            write(fd, resp.str().c_str(), resp.str().size());
        }
    }

    close(server_fd);
    return 0;
}
