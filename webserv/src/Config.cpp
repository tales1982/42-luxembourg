#include "Config.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>   // ✅ para std::atoi
#include <cstddef>   // ✅ para ptrdiff_t
#include <ios>       // ✅ para streamsize

Config::Config(const std::string& path) {
    std::ifstream file(path.c_str());
    if (!file.is_open())
        throw std::runtime_error("Could not open config file");

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            if (key == "port")
                _port = std::atoi(value.c_str());
        }
    }
}

int Config::getPort() const {
    return _port;
}
