#pragma once

#include <string>

struct ServerConfig {
    int port;
    std::string host;
    std::string root;
    std::string error_404;
    std::string error_500;

    ServerConfig()
        : port(8080),
          host("127.0.0.1"),
          root("./www"),
          error_404("./www/errors/404.html"),
          error_500("./www/errors/500.html") {}
};
