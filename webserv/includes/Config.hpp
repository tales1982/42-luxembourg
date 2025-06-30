// Config.hpp
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>


class Config {
public:
    Config(const std::string& path);
    int getPort() const;

private:
    int _port;
};

#endif
