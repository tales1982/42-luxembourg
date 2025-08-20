#include "Router.hpp"
#include "Utils.hpp"

Router::Router(const GlobalConfig &gc): _conf(gc) {}

const ServerConfig* Router::pickServer(const HttpRequest &req) const {
	std::string host = "";
	std::map<std::string,std::string>::const_iterator it = req.headers.find("Host");
	if (it != req.headers.end()) host = it->second;
	size_t colon = host.find(':');
	std::string hostOnly = (colon==std::string::npos) ? host : host.substr(0, colon);

	for (size_t i=0;i<_conf.servers.size();++i) {
		const ServerConfig &s = _conf.servers[i];
		for (size_t j=0;j<s.server_names.size();++j) {
			if (s.server_names[j] == hostOnly) return &s;
		}
	}
	for (size_t i=0;i<_conf.servers.size();++i) if (_conf.servers[i].is_default) return &_conf.servers[i];
	return _conf.servers.empty()? (ServerConfig*)0 : &_conf.servers[0];
}

const LocationConfig* Router::pickLocation(const ServerConfig *srv, const std::string &uri) const {
	const LocationConfig *best = 0;
	size_t bestLen = 0;
	for (size_t i=0;i<srv->locations.size();++i) {
		const LocationConfig &loc = srv->locations[i];
		if (Utils::startsWith(uri, loc.path) && loc.path.size() > bestLen) {
			best = &loc; bestLen = loc.path.size();
		}
	}
	return best;
}

RouteMatch Router::match(const HttpRequest &req) const {
	RouteMatch m; m.server = pickServer(req); m.loc = 0;
	if (!m.server) return m;
	m.loc = pickLocation(m.server, req.uri);
	m.fsRoot = m.server->root;
	if (m.loc && !m.loc->root.empty()) m.fsRoot = m.loc->root;
	m.relPath = req.uri;
	if (m.loc && Utils::startsWith(m.relPath, m.loc->path)) m.relPath = m.relPath.substr(m.loc->path.size());
	if (m.relPath.size() && m.relPath[0] == '/') m.relPath = m.relPath.substr(1);
	return m;
}
