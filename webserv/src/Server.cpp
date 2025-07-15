#include "../include/Server.hpp"

int ft_server(const ServerConfig& config) {
    int server_fd, new_client, max_fd;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    fd_set master_set, read_set;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Error creating socket\n";
        return 1;
    }

    fcntl(server_fd, F_SETFL, O_NONBLOCK);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(config.host.c_str());  // usa IP da config
    addr.sin_port = htons(config.port);                     // usa porta da config

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Error in bind\n";
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 10) < 0) {
        std::cerr << "Error in listen\n";
        close(server_fd);
        return 1;
    }

    std::cout << "Server listening on " << config.host << ":" << config.port << "\n";
   

    // 5. Inicializa os sets
    FD_ZERO(&master_set);
    FD_SET(server_fd, &master_set);
    max_fd = server_fd;

    while (true)
    {
        read_set = master_set;
        int activity = select(max_fd + 1, &read_set, NULL, NULL, NULL);

        if (activity < 0)
        {
            std::cerr << "Error in select\n";
            break;
        }

        // 6. Nova conexão
        if (FD_ISSET(server_fd, &read_set))
        {
            new_client = accept(server_fd, (struct sockaddr *)&addr, &addrlen);
            if (new_client < 0)
            {
                std::cerr << "Error in accept\n";
                continue;
            }

            // Torna o cliente não bloqueante
            fcntl(new_client, F_SETFL, O_NONBLOCK);

            std::cout << "New client connected! FD: " << new_client << std::endl;
            FD_SET(new_client, &master_set);
            if (new_client > max_fd)
                max_fd = new_client;
        }

        // 7. Leitura de clientes
        for (int fd = server_fd + 1; fd <= max_fd; ++fd)
        {
            if (FD_ISSET(fd, &read_set))
            {
                char buffer[1024] = {0};
                int n = read(fd, buffer, 1023);

                if (n < 0)
                {
                    if (errno == EAGAIN || errno == EWOULDBLOCK)
                        continue; // Nada pra ler agora
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
                    std::cout << "Message from client FD " << fd << ": " << buffer << std::endl;
                    write(fd, "Mensagem recebida!\n", 20);
                }
            }
        }
    }

    close(server_fd);
    return 0;
}
