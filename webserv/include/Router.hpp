#ifndef ROUTER_HPP
#define ROUTER_HPP

#include "Config.hpp"
#include "Http.hpp"
#include <string>

struct RouteMatch {
	const ServerConfig *server;
	const LocationConfig *loc;
	std::string fsRoot;
	std::string relPath;
};

class Router {
public:
	Router(const GlobalConfig &gc);
	RouteMatch match(const HttpRequest &req) const;
	const GlobalConfig &config() const { return _conf; }
private:
	const GlobalConfig &_conf;
	const ServerConfig* pickServer(const HttpRequest &req) const;
	const LocationConfig* pickLocation(const ServerConfig *srv, const std::string &uri) const;
};

#endif
