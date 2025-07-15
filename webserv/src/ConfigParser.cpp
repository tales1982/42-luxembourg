#include "../include/ConfigParser.hpp"
#include <stack>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>

// Função auxiliar para remover espaços e tabulações de início/fim da string
std::string trim(const std::string &str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

ServerConfig parse_config(const std::string &path) {
    ServerConfig server;
    std::ifstream file(path.c_str());
    if (!file.is_open()) {
        std::cerr << "Could not open config file: " << path << std::endl;
        return server;
    }

    std::string line;
    std::stack<std::string> context;
    LocationConfig current_location;
    bool in_location_block = false;

    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#')
            continue;

        // Início de um bloco
        if (line.find('{') != std::string::npos) {
            std::string blockName = trim(line.substr(0, line.find('{')));
            context.push(blockName);

            if (blockName.find("location") == 0) {
                in_location_block = true;
                std::istringstream iss(blockName);
                std::string locKeyword, locPath;
                iss >> locKeyword >> locPath;
                current_location = LocationConfig(); // reinicia
                current_location.path = locPath;
            }
            continue;
        }

        // Fim de um bloco
        if (line.find('}') != std::string::npos) {
            if (!context.empty() && context.top().find("location") == 0) {
                server.locations.push_back(current_location);
                in_location_block = false;
            }
            if (!context.empty())
                context.pop();
            continue;
        }

        // Diretivas
        std::istringstream iss(line);
        std::string key, value;
        iss >> key;
        std::getline(iss, value);
        value = trim(value);

        if (in_location_block) {
            current_location.directives[key] = value;
        } else if (!context.empty() && context.top() == "server") {
            if (key == "host") server.host = value;
            else if (key == "listen") server.port = std::atoi(value.c_str());
            else if (key == "root") server.root = value;
            else if (key == "error_page") {
                int code;
                std::string path;
                std::istringstream ep(value);
                ep >> code >> path;
                if (code == 404)
                    server.error_404 = path;
                else if (code == 500)
                    server.error_500 = path;
            } else {
                server.general_directives[key] = value;
            }
        } else if (context.empty()) {
            server.general_directives[key] = value;
        }
    }

    file.close();
    return server;
}
