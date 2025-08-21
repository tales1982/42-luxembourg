#include "Config.hpp"
#include "Server.hpp"
#include "ConfigValidation.hpp"
#include <iostream>
#include <signal.h>

// Cores ANSI
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

int main(int argc, char **argv) {
    signal(SIGPIPE, SIG_IGN);
    std::string cfg = "configs/example.conf";
    if (argc > 1) cfg = argv[1];
    try {
        std::cout << CYAN << "[INFO]" << RESET << " Loading config: " << cfg << std::endl;

        ConfigParser p;
        GlobalConfig g = p.parseFile(cfg);
        validateOrDie(g);


        if (g.servers.empty()) {
            std::cerr << RED << "[ERROR]" << RESET << " No servers defined in config" << std::endl;
            return 1;
        }

        std::cout << CYAN << "[INFO]" << RESET << " Parsed "
                  << GREEN << g.servers.size() << RESET << " server blocks" << std::endl;

        // listar cada server para debug
        for (size_t i = 0; i < g.servers.size(); ++i) {
            const ServerConfig &s = g.servers[i];
            std::cout << "  " << YELLOW << "->" << RESET
                      << " server[" << i << "] "
                      << BLUE << "listen " << RESET
                      << s.host << ":" << s.port
                      << " " << BLUE << "root=" << RESET << s.root
                      << " " << BLUE << "server_name=" << RESET;
            for (size_t j = 0; j < s.server_names.size(); ++j) {
                if (j) std::cout << ",";
                std::cout << s.server_names[j];
            }
            std::cout << std::endl;
        }

        ServerApp app(g);
        std::cout << CYAN << "[INFO]" << RESET
                  << " webserv ready, entering main loop "
                  << YELLOW << "(Ctrl+C to stop)" << RESET << std::endl;

        app.run();

    } catch (std::exception &e) {
        std::cerr << RED << "[FATAL]" << RESET << " " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
