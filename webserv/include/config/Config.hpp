#pragma once

#include <string>
#include <map>
#include <vector>

struct LocationConfig {
    std::string path;
    std::map<std::string, std::string> directives;
};

struct ServerConfig {
    int port;
    std::string host;
    std::string root;
    std::string error_404;
    std::string error_500;
    std::map<std::string, std::string> general_directives;
    std::vector<LocationConfig> locations;

    ServerConfig()
        : port(8080), host("127.0.0.1"), root("./www"),
          error_404("./www/errors/404.html"),
          error_500("./www/errors/500.html") {}
};
