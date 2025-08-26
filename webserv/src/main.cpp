#include "Config.hpp"
#include "Server.hpp"
#include "ConfigValidation.hpp"
#include <iostream>
#include <iomanip>
#include <signal.h>

// ANSI color codes for enhanced visual appeal
#define RESET   "\033[0m"
#define RED     "\033[91m"  // Bright red for errors
#define GREEN   "\033[92m"  // Bright green for success/numbers
#define YELLOW  "\033[93m"  // Bright yellow for highlights
#define BLUE    "\033[94m"  // Bright blue for labels
#define CYAN    "\033[96m"  // Bright cyan for info
#define MAGENTA "\033[95m"  // Magenta for secondary info
#define BOLD    "\033[1m"   // Bold for emphasis
#define UNDERLINE "\033[4m" // Underline for headers

int main(int argc, char **argv) {
    signal(SIGPIPE, SIG_IGN);
    std::string cfg = "configs/example.conf";
    if (argc > 1) cfg = argv[1];

    try {
        // Header for config loading
        std::cout << CYAN << BOLD << "[INFO] Configuration Loading" << RESET
                  << std::endl << std::setw(10) << " "
                  << "File: " << MAGENTA << cfg << RESET << std::endl;

        ConfigParser p;
        GlobalConfig g = p.parseFile(cfg);
        validateOrDie(g);

        // Check for empty server configs
        if (g.servers.empty()) {
            std::cerr << RED << BOLD << "[ERROR] No Server Configurations" << RESET
                      << std::endl << std::setw(10) << " "
                      << "Details: No server blocks defined in config file" << std::endl;
            return 1;
        }

        // Summary of parsed servers
        std::cout << CYAN << BOLD << "[INFO] Configuration Parsed Successfully" << RESET
                  << std::endl << std::setw(10) << " "
                  << "Total Servers: " << GREEN << g.servers.size() << RESET << std::endl;

        // Detailed server configuration listing
        std::cout << YELLOW << UNDERLINE << "[DEBUG] Server Configurations" << RESET << std::endl;
        for (size_t i = 0; i < g.servers.size(); ++i) {
            const ServerConfig &s = g.servers[i];
            std::cout << std::setw(8) << " " << YELLOW << "→" << RESET
                      << " Server[" << GREEN << i << RESET << "]" << std::endl
                      << std::setw(10) << " "
                      << BLUE << "Listen: " << RESET << s.host << ":" << GREEN << s.port << RESET << std::endl
                      << std::setw(10) << " "
                      << BLUE << "Root: " << RESET << s.root << std::endl
                      << std::setw(10) << " "
                      << BLUE << "Server Names: " << RESET;
            for (size_t j = 0; j < s.server_names.size(); ++j) {
                if (j) std::cout << ", ";
                std::cout << MAGENTA << s.server_names[j] << RESET;
            }
            std::cout << std::endl;

            // Additional debug info (example: max body size, error pages)
            std::cout << std::setw(10) << " "
                      << BLUE << "Max Body Size: " << RESET << GREEN << s.client_max_body_size
                      << RESET << " bytes" << std::endl;
            if (!s.error_pages.empty()) {
                std::cout << std::setw(10) << " "
                          << BLUE << "Error Pages: " << RESET;
                for (std::map<int, std::string>::const_iterator it = s.error_pages.begin();
                     it != s.error_pages.end(); ++it) {
                    if (it != s.error_pages.begin()) std::cout << ", ";
                    std::cout << "[" << it->first << ": " << it->second << "]";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl; // Extra spacing for readability
        }

        // Server startup message
        ServerApp app(g);
        std::cout << CYAN << BOLD << "[INFO] Web Server Starting" << RESET << std::endl
                  << std::setw(10) << " "
                  << "Status: " << GREEN << "Ready" << RESET
                  << ", entering main loop " << YELLOW << "(Ctrl+C to stop)" << RESET << std::endl;

        app.run();

    } catch (std::exception &e) {
        std::cerr << RED << BOLD << "[FATAL] Critical Error" << RESET << std::endl
                  << std::setw(10) << " "
                  << "Details: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}