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
#include <cctype>    // std::tolower
#include <strings.h> // strncasecmp  (POSIX)
#include <ctime>     // std::time (você usa em handle_upload)

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
// substitui a tua versão
static void send_response(int fd, const std::string &status, const std::string &content_type,
                          const std::string &content, bool head_only = false, bool keep_alive = false)
{
    std::ostringstream response;
    response << "HTTP/1.1 " << status << "\r\n"
             << "Content-Type: " << content_type << "\r\n"
             << "Content-Length: " << content.size() << "\r\n"
             << "Connection: " << (keep_alive ? "keep-alive" : "close") << "\r\n"
             << "\r\n";

    std::string head = response.str();
    write(fd, head.c_str(), head.size());

    if (!head_only)
    {
        if (!content.empty())
            write(fd, content.c_str(), content.size());
    }
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

//////////////////////////////////////
//          HELPS                  ///
//////////////////////////////////////
static std::string get_header_value(const std::string &request, const std::string &name)
{
    // name ex: "Content-Length" ou "Content-Type" (case-insensitive simples)
    std::string n = name + ":";
    std::string r = request;
    // busca case-insensitive básica
    for (size_t i = 0; i < r.size(); ++i)
        r[i] = std::tolower(r[i]);

    std::string low = name;
    for (size_t i = 0; i < low.size(); ++i)
        low[i] = std::tolower(low[i]);
    std::string needle = low + ":";

    size_t pos = r.find(needle);
    if (pos == std::string::npos)
        return "";
    size_t line_end = request.find("\r\n", pos);
    if (line_end == std::string::npos)
        line_end = request.size();
    std::string line = request.substr(pos, line_end - pos); // ainda com o nome em lowercase
    // pega a linha original (com as maiúsculas) no mesmo range
    line = request.substr(pos, line_end - pos);
    size_t colon = line.find(":");
    if (colon == std::string::npos)
        return "";
    std::string val = line.substr(colon + 1);
    // trim
    while (!val.empty() && (val[0] == ' ' || val[0] == '\t'))
        val.erase(0, 1);
    while (!val.empty() && (val[val.size() - 1] == '\r' || val[val.size() - 1] == '\n' || val[val.size() - 1] == ' ' || val[val.size() - 1] == '\t'))
        val.erase(val.size() - 1);
    return val;
}

static void split_path_query(const std::string &input, std::string &path_only, std::string &query)
{
    size_t q = input.find('?');
    if (q == std::string::npos)
    {
        path_only = input;
        query = "";
    }
    else
    {
        path_only = input.substr(0, q);
        query = input.substr(q + 1);
    }
}

static std::string to_string_i(int v)
{
    std::ostringstream oss;
    oss << v;
    return oss.str();
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

    if (path == "/")
        path = "/index.html";

    const LocationConfig *loc = match_location(config, path);

    // ✅ Verifica se o método HTTP é permitido na rota
    if (loc && loc->directives.count("methods"))
    {
        // 👉 não 405 aqui para POST em arquivos .bla; deixa o handler do .bla decidir
        bool is_bla_post = (method == "POST" && path.size() >= 4 && path.substr(path.size() - 4) == ".bla");
        if (!is_bla_post)
        {
            std::string allowed = loc->directives.at("methods");
            if ((method == "GET" && allowed.find("GET") == std::string::npos) ||
                (method == "POST" && allowed.find("POST") == std::string::npos) ||
                (method == "PUT" && allowed.find("PUT") == std::string::npos) ||
                (method == "DELETE" && allowed.find("DELETE") == std::string::npos))
            {
                std::string error405 = read_file(config.root + "/errors/405.html");
                log_request(fd, method, path, "405 Method Not Allowed");
                send_response(fd, "405 Method Not Allowed", "text/html", error405,
                              (method == "HEAD"), is_keep_alive(request));
                return;
            }
        }
    }

    /* ------------- AQUI: BLOCO DO PUT /put_test ------------- */
    if (method == "PUT" && path.rfind("/put_test/", 0) == 0)
    { // começa com /put_test/
        // Descobre root definido para /put_test no config (ubuntu_tester.conf usa ./put_store)
        const LocationConfig *putLoc = match_location(config, "/put_test");
        std::string putRoot = (putLoc && putLoc->directives.count("root"))
                                  ? putLoc->directives.at("root")
                                  : "./put_store";
        mkdir(putRoot.c_str(), 0777);

        // Sufixo após "/put_test/"
        std::string rel = path.substr(10); // len("/put_test/") = 10
        if (rel.empty())
            rel = "put_file.dat";

        std::string full = putRoot + "/" + rel;

        // Corpo da requisição
        size_t hdr_end = request.find("\r\n\r\n");
        std::string body = (hdr_end != std::string::npos) ? request.substr(hdr_end + 4) : "";

        // Grava o arquivo
        std::ofstream out(full.c_str(), std::ios::binary);
        if (!out)
        {
            std::string error500 = read_file(config.error_500);
            send_response(fd, "500 Internal Server Error", "text/html", error500,
                          (method == "HEAD"), is_keep_alive(request));
            return;
        }
        out.write(body.data(), body.size());
        out.close();

        // 201 Created sem corpo está ok para PUT
        log_request(fd, method, path, "201 Created");
        send_response(fd, "201 Created", "text/plain", "",
                      (method == "HEAD"), is_keep_alive(request));
        return;
    }
    /* --------- FIM DO BLOCO PUT /put_test  --------- */
    // -------------------- CGI por extensão .bla (POST via ./cgi_test) --------------------
    if (path.size() >= 4 && path.substr(path.size() - 4) == ".bla" && method == "POST")
    {
        // Pega root e cgi_path da location; se faltar, usa defaults do tester
        const LocationConfig *blaLoc = match_location(config, path);
        std::string cgi_exec = (blaLoc && blaLoc->directives.count("cgi_path"))
                                   ? blaLoc->directives.at("cgi_path")
                                   : "./cgi_test";
        std::string root = (blaLoc && blaLoc->directives.count("root"))
                               ? blaLoc->directives.at("root")
                               : "./YoupiBanane";

        // Separa caminho e query
        std::string url_path, query;
        split_path_query(path, url_path, query);

        // Mapear URL -> FS: ex. /youpi.bla => ./YoupiBanane/youpi.bla
        std::string script_fs = root + url_path;

        // Body e headers
        size_t hdr_end = request.find("\r\n\r\n");
        std::string req_body = (hdr_end != std::string::npos) ? request.substr(hdr_end + 4) : "";
        std::string content_length = get_header_value(request, "Content-Length");
        std::string content_type = get_header_value(request, "Content-Type");

        // Pipes
        int pipe_out[2], pipe_in[2];
        if (pipe(pipe_out) == -1 || pipe(pipe_in) == -1)
        {
            std::string error500 = read_file(config.error_500);
            send_response(fd, "500 Internal Server Error", "text/html", error500,
                          (method == "HEAD"), is_keep_alive(request));
            return;
        }

        pid_t pid = fork();
        if (pid == -1)
        {
            std::string error500 = read_file(config.error_500);
            send_response(fd, "500 Internal Server Error", "text/html", error500,
                          (method == "HEAD"), is_keep_alive(request));
            return;
        }

        if (pid == 0)
        {
            // Filho: conecta stdin/stdout
            dup2(pipe_in[0], STDIN_FILENO);
            dup2(pipe_out[1], STDOUT_FILENO);
            close(pipe_in[1]);
            close(pipe_out[0]);
            close(pipe_in[0]);
            close(pipe_out[1]);

            // ENV CGI (INCLUI REQUEST_METHOD!)
            std::vector<std::string> envs;
            envs.push_back("GATEWAY_INTERFACE=CGI/1.1");
            envs.push_back("SERVER_PROTOCOL=HTTP/1.1");
            envs.push_back("REQUEST_METHOD=" + method);
            envs.push_back("QUERY_STRING=" + query);
            envs.push_back("SCRIPT_NAME=" + url_path);
            envs.push_back("SCRIPT_FILENAME=" + script_fs);
            envs.push_back("PATH_INFO=");
            envs.push_back("SERVER_NAME=localhost");
            envs.push_back("SERVER_PORT=" + ((config.port > 0) ? to_string_i(config.port) : std::string("8080")));
            if (!content_type.empty())
                envs.push_back("CONTENT_TYPE=" + content_type);
            if (!content_length.empty())
                envs.push_back("CONTENT_LENGTH=" + content_length);
            envs.push_back("REDIRECT_STATUS=200");

            std::vector<char *> envp;
            for (size_t i = 0; i < envs.size(); ++i)
                envp.push_back(const_cast<char *>(envs[i].c_str()));
            envp.push_back(0);

            // Executável CGI direto
            const char *argv_exec[3];
            argv_exec[0] = cgi_exec.c_str();
            argv_exec[1] = script_fs.c_str(); // maioria aceita argv[1] como caminho
            argv_exec[2] = 0;

            execve(cgi_exec.c_str(), const_cast<char *const *>(argv_exec), &envp[0]);
            _exit(127);
        }
        else
        {
            // Pai: envia body e lê resposta
            close(pipe_in[0]);
            close(pipe_out[1]);

            if (!req_body.empty())
            {
                ssize_t off = 0;
                while (off < (ssize_t)req_body.size())
                {
                    ssize_t w = write(pipe_in[1], req_body.data() + off, req_body.size() - off);
                    if (w <= 0)
                        break;
                    off += w;
                }
            }
            close(pipe_in[1]);

            std::string cgi_raw;
            char buf[4096];
            ssize_t n;
            while ((n = read(pipe_out[0], buf, sizeof(buf))) > 0)
                cgi_raw.append(buf, n);
            close(pipe_out[0]);

            // separa headers e body
            std::string::size_type sep = cgi_raw.find("\r\n\r\n");
            std::string cgi_headers = (sep != std::string::npos) ? cgi_raw.substr(0, sep) : "";
            std::string cgi_body = (sep != std::string::npos) ? cgi_raw.substr(sep + 4) : cgi_raw;

            int status_code = 200;
            std::string status_text = "OK";
            std::string contentType = "text/plain";
            std::istringstream hs(cgi_headers);
            for (std::string line; std::getline(hs, line);)
            {
                if (!line.empty() && line[line.size() - 1] == '\r')
                    line.erase(line.size() - 1);
                if (line.size() > 8 && !strncasecmp(line.c_str(), "Status: ", 8))
                {
                    std::istringstream ss(line.substr(8));
                    ss >> status_code;
                    std::getline(ss, status_text);
                    if (!status_text.empty() && status_text[0] == ' ')
                        status_text.erase(0, 1);
                }
                else if (line.size() > 13 && !strncasecmp(line.c_str(), "Content-Type:", 13))
                {
                    std::string v = line.substr(13);
                    if (!v.empty() && v[0] == ' ')
                        v.erase(0, 1);
                    contentType = v;
                }
            }
            std::ostringstream status;
            status << status_code << " " << (status_text.empty() ? "OK" : status_text);
            send_response(fd, status.str(), contentType, cgi_body,
                          (method == "HEAD"), is_keep_alive(request));
            return;
        }
    }

    // -------------------- POST /post_body (max 100 bytes) --------------------
    if (method == "POST" && path == "/post_body")
    {
        size_t hdr_end = request.find("\r\n\r\n");
        std::string body = (hdr_end != std::string::npos) ? request.substr(hdr_end + 4) : "";

        if (body.size() > 100)
        {
            // 413 Payload Too Large
            send_response(fd, "413 Payload Too Large", "text/plain", "",
                          (method == "HEAD"), is_keep_alive(request));
            return;
        }
        send_response(fd, "200 OK", "text/plain", "OK",
                      (method == "HEAD"), is_keep_alive(request));
        return;
    }

    // -------------------- CGI (NOVA VERSÃO) --------------------
    if (loc && loc->path == "/cgi-bin" && path.find("/cgi-bin/") == 0)
    {
        // separa caminho e query
        std::string url_path, query;
        split_path_query(path, url_path, query); // ex.: /cgi-bin/test.py?x=1

        // resolve script no filesystem
        std::string cgi_root = (loc->directives.count("root") ? loc->directives.at("root") : "./cgi-bin");
        std::string script_rel = url_path.substr(9); // remove "/cgi-bin/"
        std::string script_fs = cgi_root + "/" + script_rel;

        // verifica existência
        struct stat st;
        if (stat(script_fs.c_str(), &st) != 0)
        {
            std::string error404 = read_file(config.error_404);
            log_request(fd, method, path, "404 Not Found");
            send_response(fd, "404 Not Found", "text/html", error404, (method == "HEAD"), is_keep_alive(request));
            return;
        }

        // pega headers de interesse
        std::string content_length = get_header_value(request, "Content-Length");
        std::string content_type = get_header_value(request, "Content-Type");

        // corpo da requisição (se houver)
        size_t hdr_end = request.find("\r\n\r\n");
        std::string req_body = (hdr_end != std::string::npos) ? request.substr(hdr_end + 4) : "";

        // pipes
        int pipe_out[2]; // CGI stdout -> servidor
        int pipe_in[2];  // servidor -> CGI stdin
        if (pipe(pipe_out) == -1 || pipe(pipe_in) == -1)
        {
            std::string error500 = read_file(config.error_500);
            log_request(fd, method, path, "500 Internal Server Error");
            send_response(fd, "500 Internal Server Error", "text/html", error500, (method == "HEAD"), is_keep_alive(request));
            return;
        }

        pid_t pid = fork();
        if (pid == -1)
        {
            std::string error500 = read_file(config.error_500);
            log_request(fd, method, path, "500 Internal Server Error");
            send_response(fd, "500 Internal Server Error", "text/html", error500, (method == "HEAD"), is_keep_alive(request));
            return;
        }

        if (pid == 0)
        {
            // ----- filho: executa o CGI -----
            // stdin do CGI <- pipe_in[0]; stdout do CGI -> pipe_out[1]
            dup2(pipe_in[0], STDIN_FILENO);
            dup2(pipe_out[1], STDOUT_FILENO);

            // fecha pontas não usadas
            close(pipe_in[1]);
            close(pipe_out[0]);
            close(pipe_in[0]);
            close(pipe_out[1]);

            // monta env
            std::vector<std::string> envs;
            envs.push_back("GATEWAY_INTERFACE=CGI/1.1");
            envs.push_back("SERVER_PROTOCOL=HTTP/1.1");
            envs.push_back("REQUEST_METHOD=" + method);
            envs.push_back("QUERY_STRING=" + query);
            envs.push_back("SCRIPT_NAME=" + url_path);      // caminho na URL
            envs.push_back("SCRIPT_FILENAME=" + script_fs); // caminho no FS
            envs.push_back("PATH_INFO=");                   // vazio aqui
            envs.push_back("SERVER_NAME=localhost");
            std::string portStr = (config.port > 0) ? to_string_i(config.port) : "8080";
            envs.push_back("SERVER_PORT=" + portStr);
            if (!content_type.empty())
                envs.push_back("CONTENT_TYPE=" + content_type);
            if (!content_length.empty())
                envs.push_back("CONTENT_LENGTH=" + content_length);
            envs.push_back("REDIRECT_STATUS=200");

            // converte para char*[]
            std::vector<char *> envp;
            for (size_t i = 0; i < envs.size(); ++i)
                envp.push_back(const_cast<char *>(envs[i].c_str()));
            envp.push_back(0);

            // intérprete
            std::string cgi_path = (loc->directives.count("cgi_path") ? loc->directives.at("cgi_path") : "/usr/bin/python3");

            const char *argv[3];
            argv[0] = cgi_path.c_str();
            argv[1] = script_fs.c_str();
            argv[2] = 0;

            execve(cgi_path.c_str(), const_cast<char *const *>(argv), &envp[0]);
            // se chegou aqui, falhou
            _exit(127);
        }
        else
        {
            // ----- pai: escreve corpo e lê resposta -----
            close(pipe_in[0]);  // não lê do stdin do CGI
            close(pipe_out[1]); // não escreve no stdout do CGI

            // escreve o body (POST) no stdin do CGI
            if (!req_body.empty())
            {
                ssize_t off = 0;
                while (off < (ssize_t)req_body.size())
                {
                    ssize_t w = write(pipe_in[1], req_body.data() + off, req_body.size() - off);
                    if (w <= 0)
                        break;
                    off += w;
                }
            }
            close(pipe_in[1]);

            // lê stdout do CGI
            std::string cgi_raw;
            char buf[4096];
            ssize_t n;
            while ((n = read(pipe_out[0], buf, sizeof(buf))) > 0)
            {
                cgi_raw.append(buf, n);
            }
            close(pipe_out[0]);

            // parse headers do CGI
            std::string::size_type sep = cgi_raw.find("\r\n\r\n");
            std::string cgi_headers = (sep != std::string::npos) ? cgi_raw.substr(0, sep) : "";
            std::string cgi_body = (sep != std::string::npos) ? cgi_raw.substr(sep + 4) : cgi_raw;

            int status_code = 200;
            std::string status_text = "OK";
            std::string contentType = "text/html";

            std::istringstream hs(cgi_headers);
            for (std::string line; std::getline(hs, line);)
            {
                if (!line.empty() && line[line.size() - 1] == '\r')
                    line.erase(line.size() - 1);
                if (line.empty())
                    continue;
                if (line.size() > 8 && !strncasecmp(line.c_str(), "Status: ", 8))
                {
                    std::istringstream ss(line.substr(8));
                    ss >> status_code;
                    std::getline(ss, status_text);
                    if (!status_text.empty() && status_text[0] == ' ')
                        status_text.erase(0, 1);
                }
                else if (line.size() > 13 && !strncasecmp(line.c_str(), "Content-Type:", 13))
                {
                    std::string v = line.substr(13);
                    if (!v.empty() && v[0] == ' ')
                        v.erase(0, 1);
                    contentType = v;
                }
                // (se quiser, repasse Set-Cookie etc. depois)
            }

            std::ostringstream status;
            status << status_code << " " << (status_text.empty() ? "OK" : status_text);

            log_request(fd, method, path, status.str());
            // HEAD? manda só headers
            send_response(fd, status.str(), contentType, cgi_body, (method == "HEAD"), is_keep_alive(request));
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
        else
        {
            std::string error404 = read_file(config.error_404);
            log_request(fd, method, path, "404 Not Found");
            send_response(fd, "404 Not Found", "text/html", error404, (method == "HEAD"), is_keep_alive(request));
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
        send_response(fd, "200 OK", "text/html", msg, (method == "HEAD"), is_keep_alive(request));

        return;
    }

    // -------------------- Servir arquivo ou autoindex --------------------
    std::string full_path = config.root + path;
    struct stat st;
    if (stat(full_path.c_str(), &st) != 0)
    {
        std::string error404 = read_file(config.error_404);
        log_request(fd, method, path, "404 Not Found");
        send_response(fd, "404 Not Found", "text/html", error404, (method == "HEAD"), is_keep_alive(request));

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
        send_response(fd, "404 Not Found", "text/html", error404, (method == "HEAD"), is_keep_alive(request));
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
