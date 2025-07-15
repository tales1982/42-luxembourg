#include "../include/ConfigParser.hpp"

ServerConfig parse_config(const std::string& path) {
    ServerConfig config;
    std::ifstream file(path.c_str());
    if (!file.is_open()) {
        std::cerr << "Could not open config file: " << path << std::endl;
        return config;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        iss >> key;

        if (key == "listen") {
            int port;
            iss >> port;
            config.port = port;
        } else if (key == "host") {
            std::string host;
            iss >> host;
            config.host = host;
        } else if (key == "root") {
            std::string root;
            iss >> root;
            config.root = root;
        }
        // Ignora outras linhas por enquanto
    }

    file.close();
    return config;
}
