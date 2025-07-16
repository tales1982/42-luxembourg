/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:31:30 by tales             #+#    #+#             */
/*   Updated: 2025/07/16 12:31:31 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../include/server/Server.hpp"
#include "../include/server/RequestHandler.hpp"
#include "../include/server/ResponseBuilder.hpp"
#include <fstream>
#include <sstream>
#include <arpa/inet.h> // inet_addr
#include <sys/stat.h>  // mkdir
#include <cstring>     // memset
#include <dirent.h>    // para ler diretórios

int ft_server(const ServerConfig &config)
{
    std::cout << "✔ DEBUG: Exibindo blocos location lidos:\n";
    for (size_t i = 0; i < config.locations.size(); ++i)
    {
        std::cout << "Location: " << config.locations[i].path << std::endl;
        for (std::map<std::string, std::string>::const_iterator it = config.locations[i].directives.begin(); it != config.locations[i].directives.end(); ++it)
        {
            std::cout << "  " << it->first << " = " << it->second << std::endl;
        }
    }

    int server_fd, new_client, max_fd;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    fd_set master_set, read_set;

    const size_t MAX_UPLOAD_SIZE = 104857600; // 100 MB

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
                char *buffer = new (std::nothrow) char[MAX_UPLOAD_SIZE];
                if (!buffer)
                {
                    std::cerr << "Erro ao alocar memória para upload\n";
                    continue;
                }
                memset(buffer, 0, MAX_UPLOAD_SIZE);

                int n = read(fd, buffer, MAX_UPLOAD_SIZE - 1);
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
                    std::string request(buffer, n);
                    std::cout << "Request from client FD " << fd << ":\n"
                              << request << std::endl;

                    std::string method, path;
                    std::istringstream iss(request);
                    iss >> method >> path;
                    const LocationConfig *loc = match_location(config, path);
                    if (loc && loc->directives.count("cgi_pass"))
                    {
                        std::string script_path = loc->directives.at("cgi_pass");

                        int pipe_stdout[2];
                        int pipe_stdin[2];
                        pipe(pipe_stdout); // para ler o output do CGI
                        pipe(pipe_stdin);  // para enviar o body

                        pid_t pid = fork();
                        if (pid == 0)
                        {
                            // Processo filho
                            dup2(pipe_stdout[1], STDOUT_FILENO); // Redireciona stdout
                            close(pipe_stdout[0]);               // Fecha leitura

                            std::vector<std::string> envs;
                            envs.push_back("REQUEST_METHOD=" + method);
                            envs.push_back("PATH_INFO=" + path);
                            envs.push_back("SCRIPT_NAME=" + script_path);
                            envs.push_back("SERVER_PROTOCOL=HTTP/1.1");
                            envs.push_back("GATEWAY_INTERFACE=CGI/1.1");

                            // Monta vetor de C-strings para execve
                            std::vector<char *> envp;
                            for (size_t i = 0; i < envs.size(); ++i)
                                envp.push_back(const_cast<char *>(envs[i].c_str()));
                            envp.push_back(NULL);

                            // Executa
                            char *argv[] = {const_cast<char *>(script_path.c_str()), NULL};
                            execve(script_path.c_str(), argv, &envp[0]);

                            // Se execve falhar
                            std::cerr << "Erro ao executar CGI\n";
                            exit(1);
                        }
                        else
                        {
                            // Processo pai
                            close(pipe_stdout[1]); // Fecha escrita

                            char temp[4096];
                            memset(temp, 0, sizeof(temp));
                            int bytes = read(pipe_stdout[0], temp, sizeof(temp) - 1);
                            close(pipe_stdout[0]);

                            std::ostringstream response;
                            response << "HTTP/1.1 200 OK\r\n"
                                     << "Content-Type: text/html\r\n"
                                     << "Content-Length: " << bytes << "\r\n"
                                     << "\r\n"
                                     << temp;
                            std::string resStr = response.str();
                            write(fd, resStr.c_str(), resStr.length());

                            continue;
                        }
                    }

                    if (loc)
                        std::cout << "Matched location: " << loc->path << std::endl;
                    else
                        std::cout << "No location matched!" << std::endl;

                    if (loc && loc->directives.count("return"))
                    {
                        std::istringstream ret(loc->directives.at("return"));
                        std::string code_str, url;
                        ret >> code_str >> url;

                        if ((code_str == "301" || code_str == "302" || code_str == "307" || code_str == "308") && !url.empty())
                        {
                            std::ostringstream response;
                            response << "HTTP/1.1 " << code_str << " Redirect\r\n"
                                     << "Location: " << url << "\r\n"
                                     << "Content-Length: 0\r\n\r\n";
                            std::string resStr = response.str();
                            write(fd, resStr.c_str(), resStr.length());
                            continue;
                        }
                    }

                    // --- POST /upload ---
                    if (method == "POST" && path == "/upload")
                    {
                        std::size_t body_pos = request.find("\r\n\r\n");
                        if (body_pos != std::string::npos)
                        {
                            std::string body = request.substr(body_pos + 4);

                            std::size_t file_start = body.find("\r\n\r\n");
                            std::size_t file_end = body.rfind("------");

                            if (file_start != std::string::npos && file_end != std::string::npos)
                            {
                                std::string file_content = body.substr(file_start + 4, file_end - (file_start + 4));

                                std::ostringstream oss;
                                oss << "file_" << std::time(0) << "_" << getpid();
                                std::string inferred_name = oss.str();

                                std::string extension = ".bin"; // padrão

                                // tentativa de inferir a extensão
                                if (body.find("Content-Type: image/jpeg") != std::string::npos)
                                    extension = ".jpeg";
                                else if (body.find("Content-Type: image/png") != std::string::npos)
                                    extension = ".png";
                                else if (body.find("Content-Type: application/pdf") != std::string::npos)
                                    extension = ".pdf";

                                // monta caminho final
                                std::string final_name = inferred_name + extension;
                                std::string dir = get_upload_dir_by_extension(final_name);
                                mkdir(dir.c_str(), 0777); // cria diretório se necessário

                                std::string full_path = dir + final_name;
                                std::ofstream file(full_path.c_str(), std::ios::binary);

                                if (file.is_open())
                                {
                                    file.write(file_content.c_str(), file_content.size());
                                    file.close();

                                    std::string success = read_file(config.root + "/upload_success.html");
                                    std::ostringstream response;
                                    std::string mime = get_mime_type(config.root + "/upload_success.html");
                                    response << "HTTP/1.1 200 OK\r\n"
                                             << "Content-Type: " << mime << "\r\n"
                                             << "Content-Length: " << success.length() << "\r\n"
                                             << "\r\n"
                                             << success;
                                    std::string resStr = response.str();
                                    write(fd, resStr.c_str(), resStr.length());
                                }
                                else
                                {
                                    std::string error500 = read_file(config.error_500);
                                    std::ostringstream response;
                                    response << "HTTP/1.1 500 Internal Server Error\r\n"
                                             << "Content-Type: text/html\r\n"
                                             << "Content-Length: " << error500.length() << "\r\n"
                                             << "\r\n"
                                             << error500;
                                    std::string resStr = response.str();
                                    write(fd, resStr.c_str(), resStr.length());
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

                    if (path == "/all-uploads")
                    {
                        std::string page = generate_all_uploads_page();
                        std::ostringstream response;
                        response << "HTTP/1.1 200 OK\r\n"
                                 << "Content-Type: text/html\r\n"
                                 << "Content-Length: " << page.length() << "\r\n\r\n"
                                 << page;
                        write(fd, response.str().c_str(), response.str().length());
                        continue;
                    }

                    std::string full_path = config.root + path;
                    std::string content = read_file(full_path);

                    if (content.empty())
                    {
                        struct stat st;
                        if (stat(full_path.c_str(), &st) == 0 && S_ISDIR(st.st_mode) &&
                            loc && loc->directives.count("autoindex") && loc->directives.at("autoindex") == "on")
                        {
                            std::string autoindexHtml = generate_autoindex(full_path, path);
                            std::ostringstream response;
                            std::string mime = "text/html";
                            response << "HTTP/1.1 200 OK\r\n"
                                     << "Content-Type: " << mime << "\r\n"
                                     << "Content-Length: " << autoindexHtml.length() << "\r\n"
                                     << "\r\n"
                                     << autoindexHtml;
                            std::string resStr = response.str();
                            write(fd, resStr.c_str(), resStr.length());
                        }
                        else
                        {
                            std::string error404 = read_file(config.error_404);
                            std::ostringstream response;
                            response << "HTTP/1.1 404 Not Found\r\n"
                                     << "Content-Type: text/html\r\n"
                                     << "Content-Length: " << error404.length() << "\r\n"
                                     << "\r\n"
                                     << error404;
                            std::string resStr = response.str();
                            write(fd, resStr.c_str(), resStr.length());
                        }
                    }

                    else
                    {
                        std::ostringstream response;
                        std::string mime = get_mime_type(full_path); // ✅ pega tipo correto
                        response << "HTTP/1.1 200 OK\r\n"
                                 << "Content-Type: " << mime << "\r\n"
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
