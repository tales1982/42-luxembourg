#ifndef CONFIG_VALIDATION_HPP
#define CONFIG_VALIDATION_HPP

#include "Config.hpp"
#include <stdexcept>
#include <sstream>
#include <set>
#include <string>
#include <arpa/inet.h>

inline void validateOrDie(const GlobalConfig& cfg) {
    if (cfg.servers.empty())
        throw std::runtime_error("No server blocks found in config");

    for (size_t i = 0; i < cfg.servers.size(); ++i) {
        const ServerConfig& s = cfg.servers[i];

        if (s.port <= 0 || s.port > 65535) {
            std::ostringstream oss; oss << "Invalid port " << s.port << " in server #" << i;
            throw std::runtime_error(oss.str());
        }
        // aceita "0.0.0.0" e IPv4 válidos
        struct in_addr addr;
        if (inet_aton(s.host.c_str(), &addr) == 0) {
            std::ostringstream oss; oss << "Invalid host '" << s.host << "' in server #" << i;
            throw std::runtime_error(oss.str());
        }
    }

    // OBS: múltiplos servers no MESMO host:port são permitidos (vhosts por server_name).
    // O primeiro que aparece para um host:port é o default — tua Router já lida com isso.
}

#endif
