// Config.hpp
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <map>
#include <vector>

struct ServerConfig {
    int port;
    std::string server_name;
    std::string root;
    std::string index;
    std::map<int, std::string> error_pages;

    ServerConfig() : port(8080), server_name("localhost"), root("www"), index("index.html") {}
};

class Config {
public:
    Config(const std::string& path);
    const std::vector<ServerConfig>& getServers() const;

private:
    std::vector<ServerConfig> _servers;
    void parseConfigFile(const std::string& path);
};

#endif
