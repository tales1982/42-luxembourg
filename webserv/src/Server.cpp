#include "../include/Server.hpp"
#include <fstream>
#include <sstream>
#include <arpa/inet.h> // inet_addr
#include <sys/stat.h>  // mkdir

// Lê um arquivo do disco e retorna seu conteúdo como string
std::string read_file(const std::string &path)
{
    std::ifstream file(path.c_str());
    if (!file.is_open())
        return "";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Extrai o caminho da URL da requisição HTTP (ex: "/index.html")
std::string get_requested_path(const std::string &request)
{
    std::istringstream iss(request);
    std::string method, path;
    iss >> method >> path;
    return path;
}

int ft_server(const ServerConfig &config)
{
    int server_fd, new_client, max_fd;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    fd_set master_set, read_set;

    // Criação do socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        std::cerr << "Error creating socket\n";
        return 1;
    }

    fcntl(server_fd, F_SETFL, O_NONBLOCK);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(config.host.c_str());
    addr.sin_port = htons(config.port);

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        std::cerr << "Error in bind\n";
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 10) < 0)
    {
        std::cerr << "Error in listen\n";
        close(server_fd);
        return 1;
    }

    std::cout << "Server listening on " << config.host << ":" << config.port << "\n";

    FD_ZERO(&master_set);
    FD_SET(server_fd, &master_set);
    max_fd = server_fd;

    mkdir("./uploads", 0777); // Cria pasta de uploads

    while (true)
    {
        read_set = master_set;
        int activity = select(max_fd + 1, &read_set, NULL, NULL, NULL);

        if (activity < 0)
        {
            std::cerr << "Error in select\n";
            break;
        }

        if (FD_ISSET(server_fd, &read_set))
        {
            new_client = accept(server_fd, (struct sockaddr *)&addr, &addrlen);
            if (new_client < 0)
            {
                std::cerr << "Error in accept\n";
                continue;
            }

            fcntl(new_client, F_SETFL, O_NONBLOCK);
            std::cout << "New client connected! FD: " << new_client << std::endl;
            FD_SET(new_client, &master_set);
            if (new_client > max_fd)
                max_fd = new_client;
        }

        for (int fd = server_fd + 1; fd <= max_fd; ++fd)
        {
            if (FD_ISSET(fd, &read_set))
            {
                char buffer[65536] = {0};
                int n = read(fd, buffer, 65535);
                std::cout << "Raw POST content:\n"
                          << buffer << std::endl;

                if (n < 0)
                {
                    if (errno == EAGAIN || errno == EWOULDBLOCK)
                        continue;
                    std::cerr << "Read error on FD " << fd << std::endl;
                    close(fd);
                    FD_CLR(fd, &master_set);
                }
                else if (n == 0)
                {
                    std::cout << "Client disconnected. FD: " << fd << std::endl;
                    close(fd);
                    FD_CLR(fd, &master_set);
                }
                else if (n > 0)
                {
                    std::string request(buffer);
                    std::cout << "Request from client FD " << fd << ":\n"
                              << request << std::endl;

                    std::string method, path;
                    std::istringstream iss(request);
                    iss >> method >> path;

                    // --- POST /upload ---
                    if (method == "POST" && path == "/upload")
                    {
                        std::size_t body_pos = request.find("\r\n\r\n");
                        if (body_pos != std::string::npos)
                        {
                            std::string body = request.substr(body_pos + 4);

                            // Extrai o conteúdo real ignorando cabeçalhos multipart
                            std::size_t file_start = body.find("\r\n\r\n");
                            std::size_t file_end = body.rfind("------");

                            if (file_start != std::string::npos && file_end != std::string::npos)
                            {
                                std::string file_content = body.substr(file_start + 4, file_end - (file_start + 4));

                                std::ofstream file("./uploads/uploaded_file.txt");
                                if (file.is_open())
                                {
                                    file << file_content;
                                    file.close();
                                    std::string success = read_file(config.root + "/upload_success.html");
                                    std::ostringstream response;
                                    response << "HTTP/1.1 200 OK\r\n"
                                             << "Content-Type: text/html\r\n"
                                             << "Content-Length: " << success.length() << "\r\n"
                                             << "\r\n"
                                             << success;
                                    std::string resStr = response.str();
                                    write(fd, resStr.c_str(), resStr.length());
                                }
                                else
                                {
                                    std::string err = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n";
                                    write(fd, err.c_str(), err.length());
                                }
                            }
                            else
                            {
                                std::string bad = "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
                                write(fd, bad.c_str(), bad.length());
                            }
                        }
                        else
                        {
                            std::string bad = "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
                            write(fd, bad.c_str(), bad.length());
                        }

                        continue;
                    }

                    // --- GET padrão ---
                    if (path == "/")
                        path = "/index.html";

                    std::string full_path = config.root + path;
                    std::string content = read_file(full_path);

                    if (content.empty())
                    {
                        std::string notfound = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
                        write(fd, notfound.c_str(), notfound.length());
                    }
                    else
                    {
                        std::ostringstream response;
                        response << "HTTP/1.1 200 OK\r\n"
                                 << "Content-Type: text/html\r\n"
                                 << "Content-Length: " << content.length() << "\r\n"
                                 << "\r\n"
                                 << content;
                        std::string resStr = response.str();
                        write(fd, resStr.c_str(), resStr.length());
                    }
                }
            }
        }
    }

    close(server_fd);
    return 0;
}
