// src/main.cpp
#include "Server.hpp"
#include "Config.hpp"
#include <iostream>

int main(int argc, char** argv) {
    std::string configPath = "config/default.conf";
    if (argc == 2) {
        configPath = argv[1];
    }

    try {
        Config config(configPath);
        Server server(config.getServers()[0]);
        server.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
