#include "Config.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

Config::Config(const std::string& path) {
    parseConfigFile(path);
}

const std::vector<ServerConfig>& Config::getServers() const {
    return _servers;
}

void Config::parseConfigFile(const std::string& path) {
    std::ifstream file(path.c_str());
    if (!file.is_open())
        throw std::runtime_error("Could not open config file");

    std::string line;
    ServerConfig current;
    bool inServerBlock = false;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        iss >> key;

        if (key.empty() || key[0] == '#')
            continue;

        if (key == "server") {
            inServerBlock = true;
        } else if (key == "}") {
            if (inServerBlock) {
                _servers.push_back(current);
                current = ServerConfig(); // Reset
                inServerBlock = false;
            }
        } else if (key == "listen") {
            std::string portStr;
            iss >> portStr;
            if (!portStr.empty() && portStr[portStr.size() - 1] == ';')
                portStr.erase(portStr.size() - 1);
            current.port = std::atoi(portStr.c_str());
        } else if (key == "server_name") {
            iss >> current.server_name;
            if (!current.server_name.empty() && current.server_name[current.server_name.size() - 1] == ';')
                current.server_name.erase(current.server_name.size() - 1);
        } else if (key == "root") {
            iss >> current.root;
            if (!current.root.empty() && current.root[current.root.size() - 1] == ';')
                current.root.erase(current.root.size() - 1);
        } else if (key == "index") {
            iss >> current.index;
            if (!current.index.empty() && current.index[current.index.size() - 1] == ';')
                current.index.erase(current.index.size() - 1);
        } else if (key == "error_page") {
            int code;
            std::string path;
            iss >> code >> path;
            if (!path.empty() && path[path.size() - 1] == ';')
                path.erase(path.size() - 1);
            current.error_pages[code] = path;
        }
    }

    if (_servers.empty()) {
        throw std::runtime_error("No server block found in config");
    }

    // Debug (opcional)
    for (size_t i = 0; i < _servers.size(); ++i) {
        std::cout << "[CONFIG] Servidor carregado:" << std::endl;
        std::cout << "  Port: " << _servers[i].port << std::endl;
        std::cout << "  Root: " << _servers[i].root << std::endl;
        std::cout << "  Index: " << _servers[i].index << std::endl;
        std::cout << "  Server name: " << _servers[i].server_name << std::endl;
    }
}
