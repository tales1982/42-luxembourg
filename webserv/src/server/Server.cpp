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

/////////////////////////////////////////////
///     Suporte a leitura do cobecario  /////
/////////////////////////////////////////////
bool is_keep_alive(const std::string &request)
{
    std::size_t pos = request.find("Connection:");
    if (pos != std::string::npos)
    {
        std::size_t end = request.find("\r\n", pos);
        std::string header = request.substr(pos, end - pos);
        if (header.find("keep-alive") != std::string::npos)
            return true;
    }
    return false;
}

///////////////////////////////////////
// Exibe os Logs completos do sitema //
///////////////////////////////////////
static void log_request(int fd, const std::string &method, const std::string &path, const std::string &status)
{
    std::ostringstream oss;
    oss << "[LOG] FD " << fd << " | " << method << " " << path << " => " << status << "\n";
    std::cout << oss.str();
}

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

    // Gerar nome único
    std::ostringstream oss;
    oss << "file_" << std::time(0) << "_" << getpid();
    std::string inferred_name = oss.str();

    // Criar mapa de content-types para extensões (C++98 style)
    std::map<std::string, std::string> content_type_map;
    content_type_map["image/jpeg"] = ".jpeg";
    content_type_map["image/png"] = ".png";
    content_type_map["application/pdf"] = ".pdf";
    content_type_map["text/plain"] = ".txt";
    content_type_map["application/json"] = ".json";
    content_type_map["application/zip"] = ".zip";
    content_type_map["text/html"] = ".html";
    content_type_map["application/octet-stream"] = ".bin"; // padrão

    std::string extension = ".bin"; // fallback

    // Detectar Content-Type no corpo do upload
    std::map<std::string, std::string>::const_iterator it;
    for (it = content_type_map.begin(); it != content_type_map.end(); ++it)
    {
        if (body.find(it->first) != std::string::npos)
        {
            extension = it->second;
            break;
        }
    }

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
// - Executa deleção de arquivos para método DELETE                         //
//   (verifica se DELETE é permitido no location, usa unlink no arquivo)    //
// - Serve index.html para raiz                                             //
// - Gera página de todas as uploads (/all-uploads)                         //
// - Lê arquivo do sistema de arquivos ou gera autoindex para diretórios    //
// - Retorna 200, 204, 404, 405 ou 500 conforme apropriado                  //
//////////////////////////////////////////////////////////////////////////////
static void process_client_request(int fd, const std::string &request, const ServerConfig &config, fd_set &master_set)
{
    (void)&master_set;
    std::string method, path;
    std::istringstream iss(request);
    iss >> method >> path;
    

    // ✅ Trata POST / antes de validar métodos permitidos
    if (method == "POST" && path == "/")
    {
        std::string msg = "<html><body><h1>POST recebido com sucesso</h1></body></html>";
        log_request(fd, method, path, "200 OK");
        send_response(fd, "200 OK", "text/html", msg);
        return;
    }

    // ✅ Atualiza path para index.html
    if (path == "/")
        path = "/index.html";

    const LocationConfig *loc = match_location(config, path);

    // ✅ Verifica se o método HTTP é permitido na rota
    if (loc && loc->directives.count("methods"))
    {
        std::string allowed = loc->directives.at("methods");

        if ((method == "GET" && allowed.find("GET") == std::string::npos) ||
            (method == "POST" && allowed.find("POST") == std::string::npos) ||
            (method == "PUT" && allowed.find("PUT") == std::string::npos) ||
            (method == "DELETE" && allowed.find("DELETE") == std::string::npos))
        {
            std::string error405 = read_file(config.root + "/errors/405.html");
            log_request(fd, method, path, "405 Method Not Allowed");
            send_response(fd, "405 Method Not Allowed", "text/html", error405);
            return;
        }
    }

    /*
    ////////////////////////////////////////
    // TESTE PARA CAMINHOS PROTEGIDO     ///
    // http://localhost:8080/protegido   ///
    // ERRO 401                          ///
    ////////////////////////////////////////
      if (path == "/protegido") {
            std::string error401 = read_file(config.root + "/errors/401.html");
            send_response(fd, "401 Unauthorized", "text/html", error401);
            return;
        }

    */

    // -------------------- CGI --------------------
    if (loc && loc->path == "/cgi-bin" && path.find("/cgi-bin/") == 0)
    {
        std::string script_name = path;
        std::string path_info = "";
        std::string script_path = loc->directives.at("root") + "/" + path.substr(9);

        struct stat st;
        if (stat(script_path.c_str(), &st) == 0 && (st.st_mode & S_IXUSR))
        {
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

                std::string content_length = "";
                std::string content_type = "";
                size_t header_end = request.find("\r\n\r\n");
                if (header_end != std::string::npos)
                {
                    std::istringstream header_stream(request.substr(0, header_end));
                    std::string header_line;
                    while (std::getline(header_stream, header_line))
                    {
                        if (header_line.find("Content-Length:") != std::string::npos)
                            content_length = header_line.substr(header_line.find(":") + 1);
                        if (header_line.find("Content-Type:") != std::string::npos)
                            content_type = header_line.substr(header_line.find(":") + 1);
                    }
                }

                std::vector<std::string> envs;
                envs.push_back("REQUEST_METHOD=" + method);
                envs.push_back("SCRIPT_NAME=" + script_name);
                envs.push_back("PATH_INFO=" + path_info);
                envs.push_back("SERVER_PROTOCOL=HTTP/1.1");
                envs.push_back("GATEWAY_INTERFACE=CGI/1.1");
                envs.push_back("CONTENT_LENGTH=" + content_length);
                envs.push_back("CONTENT_TYPE=" + content_type);
                envs.push_back("REDIRECT_STATUS=200");

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

                std::string cgi_output;
                char buffer[1024];
                int bytes_read;

                while ((bytes_read = read(pipe_stdout[0], buffer, sizeof(buffer))) > 0)
                    cgi_output.append(buffer, bytes_read);

                close(pipe_stdout[0]);

                size_t body_start = cgi_output.find("\r\n\r\n");
                std::string body = (body_start != std::string::npos)
                                       ? cgi_output.substr(body_start + 4)
                                       : cgi_output;

                log_request(fd, method, path, "200 OK");
                send_response(fd, "200 OK", "text/html", body);
                return;
            }
        }
        else
        {
            std::string error404 = read_file(config.error_404);
            log_request(fd, method, path, "404 Not Found");
            send_response(fd, "404 Not Found", "text/html", error404);
            return;
        }
    }

    // -------------------- Redirecionamento --------------------
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
            log_request(fd, method, path, code_str + " Redirect");
            write(fd, response.str().c_str(), response.str().length());
            return;
        }
    }

    // -------------------- Upload --------------------
    if (method == "POST" && path == "/upload")
    {
        handle_upload(fd, request, config);
        log_request(fd, method, path, "200 OK");
        return;
    }

    // -------------------- DELETE --------------------
    if (method == "DELETE")
    {
        if (loc && loc->directives.count("methods"))
        {
            std::string allowed = loc->directives.at("methods");

            if ((method == "GET" && allowed.find("GET") == std::string::npos) ||
                (method == "POST" && allowed.find("POST") == std::string::npos) ||
                (method == "DELETE" && allowed.find("DELETE") == std::string::npos))
            {
                std::string error405 = read_file(config.root + "/errors/405.html");
                std::ostringstream response;
                response << "HTTP/1.1 405 Method Not Allowed\r\n"
                         << "Allow: " << allowed << "\r\n"
                         << "Content-Type: text/html\r\n"
                         << "Content-Length: " << error405.length() << "\r\n\r\n"
                         << error405;

                log_request(fd, method, path, "405 Method Not Allowed");
                write(fd, response.str().c_str(), response.str().length());
                return;
            }
        }

        std::string full_path = config.root + path;

        struct stat st;
        if (stat(full_path.c_str(), &st) == 0 && S_ISREG(st.st_mode))
        {
            if (unlink(full_path.c_str()) == 0)
            {
                std::cout << "✔ Arquivo deletado: " << full_path << std::endl;
                log_request(fd, method, path, "204 No Content");
                send_response(fd, "204 No Content", "text/plain", "");
            }
            else
            {
                std::string error500 = read_file(config.error_500);
                log_request(fd, method, path, "500 Internal Server Error");
                send_response(fd, "500 Internal Server Error", "text/html", error500);
            }
        }
        else
        {
            std::string error404 = read_file(config.error_404);
            log_request(fd, method, path, "404 Not Found");
            send_response(fd, "404 Not Found", "text/html", error404);
        }
        return;
    }

    // --- /all-uploads ---
    if (path == "/all-uploads")
    {
        std::string page = generate_all_uploads_page();
        log_request(fd, method, path, "200 OK");
        send_response(fd, "200 OK", "text/html", page);
        return;
    }

    // --- POST direto em /index.html ---
    if (method == "POST" && path == "/index.html")
    {
        std::string msg = "<html><body><h1>POST recebido com sucesso</h1></body></html>";
        log_request(fd, method, path, "200 OK");
        send_response(fd, "200 OK", "text/html", msg);
        return;
    }

    // -------------------- Servir arquivo ou autoindex --------------------
    std::string full_path = config.root + path;
    struct stat st;
    if (stat(full_path.c_str(), &st) != 0)
    {
        std::string error404 = read_file(config.error_404);
        log_request(fd, method, path, "404 Not Found");
        send_response(fd, "404 Not Found", "text/html", error404);
        return;
    }

    // Verificar permissão de leitura
    if (access(full_path.c_str(), R_OK) != 0)
    {
        std::string error403 = read_file(config.root + "/errors/403.html");
        log_request(fd, method, path, "403 Forbidden");
        send_response(fd, "403 Forbidden", "text/html", error403);
        return;
    }

    // Se for diretório e autoindex estiver ativado
    if (S_ISDIR(st.st_mode) &&
        loc && loc->directives.count("autoindex") &&
        loc->directives.at("autoindex") == "on")
    {
        std::string autoindexHtml = generate_autoindex(full_path, path);
        log_request(fd, method, path, "200 OK");
        send_response(fd, "200 OK", "text/html", autoindexHtml);
        return;
    }

    // Se não for diretório, tentar ler o conteúdo
    std::string content = read_file(full_path);
    if (content.empty())
    {
        std::string error404 = read_file(config.error_404);
        log_request(fd, method, path, "404 Not Found");
        send_response(fd, "404 Not Found", "text/html", error404);
    }
    else
    {
        log_request(fd, method, path, "200 OK");
        send_response(fd, "200 OK", get_mime_type(full_path), content);
    }
    if (!is_keep_alive(request))
    {
        std::cout << "🔌 Fechando conexão (sem keep-alive): FD " << fd << "\n";
        if (FD_ISSET(fd, &master_set))
        {
            close(fd);
            FD_CLR(fd, &master_set);
        }
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
        struct timeval timeout;
        timeout.tv_sec = 10; // timeout de 10 segundos
        timeout.tv_usec = 0;
        int activity = select(max_fd + 1, &read_set, NULL, NULL, &timeout);

        if (activity == 0)
        {
            // Timeout sem atividade
            continue;
        }

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

                size_t total_read = 0;
                int n = 0;

                while (true)
                {
                    n = read(fd, buffer + total_read, MAX_UPLOAD_SIZE - 1 - total_read);
                    if (n < 0)
                    {
                        if (errno == EAGAIN || errno == EWOULDBLOCK)
                            break;
                        std::cerr << "Read error on FD " << fd << std::endl;
                        close(fd);
                        FD_CLR(fd, &master_set);
                        delete[] buffer;
                        continue; // ✅ substitui o return inválido
                    }
                    else if (n == 0)
                    {
                        // Fim da transmissão
                        break;
                    }
                    else
                    {
                        total_read += n;
                        if (total_read >= MAX_UPLOAD_SIZE - 1)
                            break;
                    }
                }

                if (total_read > 0)
                {
                    buffer[total_read] = '\0';
                    std::string request(buffer, total_read);
                    std::cout << "Request from client FD " << fd << ":\n"
                              << request << std::endl;
                    process_client_request(fd, request, config, master_set);
                }
                else
                {
                    std::cerr << "Conexão sem dados recebidos. FD: " << fd << std::endl;
                    close(fd);
                    FD_CLR(fd, &master_set);
                }

                delete[] buffer;
            }
        }
    }

    close(server_fd);
    return 0;
}
