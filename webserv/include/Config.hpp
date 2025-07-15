#pragma once

#include <string>

struct ServerConfig {
    int port;
    std::string host;
    std::string root;

    ServerConfig() : port(8080), host("127.0.0.1"), root("./www") {}
};
