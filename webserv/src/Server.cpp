#include "../include/Server.hpp"
#include <fstream>
#include <sstream>
#include <arpa/inet.h> // necessário para inet_addr

// Função auxiliar para ler o conteúdo de um arquivo e retornar como string
std::string read_file(const std::string &path) {
    std::ifstream file(path.c_str());
    if (!file.is_open())
        return "";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Função auxiliar para extrair o caminho da URL (ex: GET /about → /about)
std::string get_requested_path(const std::string &request) {
    std::istringstream iss(request);
    std::string method, path;
    iss >> method >> path;
    return path;
}

// Função principal do servidor HTTP
int ft_server(const ServerConfig &config) {
    int server_fd, new_client, max_fd;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    fd_set master_set, read_set;

    // 1. Criação do socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Error creating socket\n";
        return 1;
    }

    // 2. Torna o socket não bloqueante
    fcntl(server_fd, F_SETFL, O_NONBLOCK);

    // 3. Permite reutilizar o mesmo endereço rapidamente
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 4. Configura IP e porta do servidor a partir da config
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(config.host.c_str());
    addr.sin_port = htons(config.port);

    // 5. Faz bind
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        std::cerr << "Error in bind\n";
        close(server_fd);
        return 1;
    }

    // 6. Começa a escutar
    if (listen(server_fd, 10) < 0) {
        std::cerr << "Error in listen\n";
        close(server_fd);
        return 1;
    }

    std::cout << "Server listening on " << config.host << ":" << config.port << "\n";

    // 7. Inicializa os conjuntos de FDs
    FD_ZERO(&master_set);
    FD_SET(server_fd, &master_set);
    max_fd = server_fd;

    // 8. Loop principal
    while (true) {
        read_set = master_set;
        int activity = select(max_fd + 1, &read_set, NULL, NULL, NULL);

        if (activity < 0) {
            std::cerr << "Error in select\n";
            break;
        }

        // 9. Verifica nova conexão
        if (FD_ISSET(server_fd, &read_set)) {
            new_client = accept(server_fd, (struct sockaddr *)&addr, &addrlen);
            if (new_client < 0) {
                std::cerr << "Error in accept\n";
                continue;
            }

            fcntl(new_client, F_SETFL, O_NONBLOCK); // não bloqueante
            std::cout << "New client connected! FD: " << new_client << std::endl;
            FD_SET(new_client, &master_set);
            if (new_client > max_fd)
                max_fd = new_client;
        }

        // 10. Lê dados de clientes existentes
        for (int fd = server_fd + 1; fd <= max_fd; ++fd) {
            if (FD_ISSET(fd, &read_set)) {
                char buffer[1024] = {0};
                int n = read(fd, buffer, 1023);

                if (n < 0) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK)
                        continue;
                    std::cerr << "Read error on FD " << fd << std::endl;
                    close(fd);
                    FD_CLR(fd, &master_set);
                }
                else if (n == 0) {
                    std::cout << "Client disconnected. FD: " << fd << std::endl;
                    close(fd);
                    FD_CLR(fd, &master_set);
                }
                else if (n > 0) {
                    std::string request(buffer);
                    std::cout << "Request from client FD " << fd << ":\n" << request << std::endl;

                    std::string path = get_requested_path(request);
                    if (path == "/")
                        path = "/index.html";

                    std::string full_path = config.root + path;
                    std::string content = read_file(full_path);

                    if (content.empty()) {
                        std::string notfound = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
                        write(fd, notfound.c_str(), notfound.length());
                    } else {
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

    // 11. Fecha o socket principal ao sair
    close(server_fd);
    return 0;
}
