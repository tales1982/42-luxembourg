/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:31:30 by tales             #+#    #+#             */
/*   Updated: 2025/07/16 17:33:50 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server/Server.hpp"
#include "../include/server/RequestHandler.hpp"
#include "../include/server/ResponseBuilder.hpp"
#include <fstream>
#include <sstream>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <cstring>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

//////////////////////////////////////////////////////////
// Inicializa o servidor com base na configuração:      //
// - Cria socket TCP não bloqueante                     //
// - Define opção SO_REUSEADDR para reuso de porta      //
// - Realiza bind() ao endereço e porta                 //
// - Invoca listen() para começar a escuta              //
// Retorna descritor do socket ou -1 em erro            //
//////////////////////////////////////////////////////////
static int initialize_server(const ServerConfig &config, struct sockaddr_in &addr)
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        std::cerr << "Error creating socket\n";
        return -1;
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
        return -1;
    }

    if (listen(server_fd, 10) < 0)
    {
        std::cerr << "Error in listen\n";
        close(server_fd);
        return -1;
    }

    std::cout << "Server listening on " << config.host << ":" << config.port << "\n";
    return server_fd;
}


//////////////////////////////////////////////////////////
// Trata nova conexão de cliente:                       //
// - Accept no socket do servidor                       //
// - Configura o novo descritor como não bloqueante     //
// - Adiciona ao conjunto de descritores master_set     //
// - Atualiza max_fd                                    //
//////////////////////////////////////////////////////////
static int handle_new_connection(int server_fd, fd_set &master_set, int &max_fd, struct sockaddr_in &addr, socklen_t addrlen)
{
    int new_client = accept(server_fd, (struct sockaddr *)&addr, &addrlen);
    if (new_client < 0)
    {
        std::cerr << "Error in accept\n";
        return -1;
    }

    fcntl(new_client, F_SETFL, O_NONBLOCK);
    std::cout << "New client connected! FD: " << new_client << std::endl;
    FD_SET(new_client, &master_set);
    if (new_client > max_fd)
        max_fd = new_client;
    return new_client;
}
//////////////////////////////////////////////////////
// Envia resposta HTTP ao cliente:                  //
// - Monta status line, headers de tipo e tamanho   //
// - Envia corpo da mensagem                        //
//////////////////////////////////////////////////////
static void send_response(int fd, const std::string &status, const std::string &content_type, const std::string &content)
{
    std::ostringstream response;
    response << "HTTP/1.1 " << status << "\r\n"
             << "Content-Type: " << content_type << "\r\n"
             << "Content-Length: " << content.length() << "\r\n"
             << "\r\n"
             << content;
    std::string resStr = response.str();
    write(fd, resStr.c_str(), resStr.length());
}

//////////////////////////////////////////////////////////
// Processa uploads multipart em /upload:               //
// - Separa cabeçalhos do corpo                         //
// - Extrai arquivo entre delimitadores                 //
// - Gera nome e extensão baseado em Content-Type       //
// - Cria diretório e salva arquivo                     //
// - Retorna página de sucesso ou erro 500              //
//////////////////////////////////////////////////////////
static void handle_upload(int fd, const std::string &request, const ServerConfig &config)
{
    std::size_t body_pos = request.find("\r\n\r\n");
    if (body_pos == std::string::npos)
    {
        send_response(fd, "400 Bad Request", "text/plain", "");
        return;
    }

    std::string body = request.substr(body_pos + 4);
    std::size_t file_start = body.find("\r\n\r\n");
    std::size_t file_end = body.rfind("------");

    if (file_start == std::string::npos || file_end == std::string::npos)
    {
        send_response(fd, "400 Bad Request", "text/plain", "");
        return;
    }

    std::string file_content = body.substr(file_start + 4, file_end - (file_start + 4));
    std::ostringstream oss;
    oss << "file_" << std::time(0) << "_" << getpid();
    std::string inferred_name = oss.str();

    std::string extension = ".bin";
    if (body.find("Content-Type: image/jpeg") != std::string::npos)
        extension = ".jpeg";
    else if (body.find("Content-Type: image/png") != std::string::npos)
        extension = ".png";
    else if (body.find("Content-Type: application/pdf") != std::string::npos)
        extension = ".pdf";

    std::string final_name = inferred_name + extension;
    std::string dir = get_upload_dir_by_extension(final_name);
    mkdir(dir.c_str(), 0777);

    std::string full_path = dir + final_name;
    std::ofstream file(full_path.c_str(), std::ios::binary);

    if (file.is_open())
    {
        file.write(file_content.c_str(), file_content.size());
        file.close();
        std::string success = read_file(config.root + "/upload_success.html");
        send_response(fd, "200 OK", get_mime_type(config.root + "/upload_success.html"), success);
    }
    else
    {
        std::string error500 = read_file(config.error_500);
        send_response(fd, "500 Internal Server Error", "text/html", error500);
    }
}
//////////////////////////////////////////////////////////////////////////////
// Processa requisição genérica de cliente:                                 //
// - Analisa método e caminho                                               //
// - Verifica diretivas CGI e executa script via fork+execve                //
// - Trata redirecionamentos usando diretiva 'return'                       //
// - Chama handle_upload para POST /upload                                  //
// - Serve index.html para raiz                                             //
// - Gera página de todas as uploads (/all-uploads)                         //
// - Lê arquivo do sistema de arquivos ou gera autoindex para diretórios    //
// - Retorna 200, 404 ou 500 conforme apropriado                            //
//////////////////////////////////////////////////////////////////////////////
static void process_client_request(int fd, const std::string &request, const ServerConfig &config, fd_set &master_set)
{
    (void)&master_set;
    std::string method, path;
    std::istringstream iss(request);
    iss >> method >> path;

    const LocationConfig *loc = match_location(config, path);

    if (loc && loc->directives.count("cgi_pass"))
    {
        std::string script_path = loc->directives.at("cgi_pass");
        int pipe_stdout[2], pipe_stdin[2];
        pipe(pipe_stdout);
        pipe(pipe_stdin);

        pid_t pid = fork();
        if (pid == 0)
        {
            dup2(pipe_stdout[1], STDOUT_FILENO);
            close(pipe_stdout[0]);
            close(pipe_stdin[1]);
            close(pipe_stdin[0]);

            std::vector<std::string> envs;
            envs.push_back("REQUEST_METHOD=" + method);
            envs.push_back("PATH_INFO=" + path);
            envs.push_back("SCRIPT_NAME=" + script_path);
            envs.push_back("SERVER_PROTOCOL=HTTP/1.1");
            envs.push_back("GATEWAY_INTERFACE=CGI/1.1");

            std::vector<char *> envp;
            for (size_t i = 0; i < envs.size(); ++i)
                envp.push_back(const_cast<char *>(envs[i].c_str()));
            envp.push_back(NULL);

            char *argv[] = {const_cast<char *>(script_path.c_str()), NULL};
            execve(script_path.c_str(), argv, &envp[0]);
            std::cerr << "Erro ao executar CGI\n";
            exit(1);
        }
        else
        {
            close(pipe_stdout[1]);
            close(pipe_stdin[0]);
            close(pipe_stdin[1]);

            char temp[4096];
            memset(temp, 0, sizeof(temp));
            int bytes = read(pipe_stdout[0], temp, sizeof(temp) - 1);
            close(pipe_stdout[0]);

            send_response(fd, "200 OK", "text/html", std::string(temp, bytes));
            return;
        }
    }

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
            return;
        }
    }

    if (method == "POST" && path == "/upload")
    {
        handle_upload(fd, request, config);
        return;
    }

    if (path == "/")
        path = "/index.html";

    if (path == "/all-uploads")
    {
        std::string page = generate_all_uploads_page();
        send_response(fd, "200 OK", "text/html", page);
        return;
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
            send_response(fd, "200 OK", "text/html", autoindexHtml);
        }
        else
        {
            std::string error404 = read_file(config.error_404);
            send_response(fd, "404 Not Found", "text/html", error404);
        }
    }
    else
    {
        send_response(fd, "200 OK", get_mime_type(full_path), content);
    }
}

//////////////////////////////////////////////////////////////////////////////
// Função principal do servidor:                                            //
// - Exibe configurações de locations para debug                            //
// - Inicializa socket e sets de descritores                                //
// - Cria diretório de uploads                                              //
// - Loop de evento select() para aceitar ou ler dados de clientes          //
// - Em leitura, aloca buffer, lê request e chama process_client_request    //
// - Fecha conexões e limpa sets quando clientes desconectam ou erro        //
//////////////////////////////////////////////////////////////////////////////
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

    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    fd_set master_set, read_set;
    int max_fd;

    const size_t MAX_UPLOAD_SIZE = 104857600; // 100 MB

    int server_fd = initialize_server(config, addr);
    if (server_fd == -1)
        return 1;

    FD_ZERO(&master_set);
    FD_SET(server_fd, &master_set);
    max_fd = server_fd;

    mkdir("./Uploads", 0777);

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
            handle_new_connection(server_fd, master_set, max_fd, addr, addrlen);
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
                std::cout << "Raw POST content:\n" << buffer << std::endl;

                if (n < 0)
                {
                    if (errno == EAGAIN || errno == EWOULDBLOCK)
                    {
                        delete[] buffer;
                        continue;
                    }
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
                else
                {
                    std::string request(buffer, n);
                    std::cout << "Request from client FD " << fd << ":\n" << request << std::endl;
                    process_client_request(fd, request, config, master_set);
                }
                delete[] buffer;
            }
        }
    }

    close(server_fd);
    return 0;
}