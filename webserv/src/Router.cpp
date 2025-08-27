#include "Router.hpp"
#include "Utils.hpp"
#include <cstdlib>
#include <string>

Router::Router(const GlobalConfig &gc): _conf(gc) {}

#include <vector> // se ainda não tiver

const ServerConfig* Router::pickServer(const HttpRequest &req) const {
    // 1) Host bruto
    std::string hostHdr;
    std::map<std::string,std::string>::const_iterator it = req.headers.find("Host");
    if (it != req.headers.end()) hostHdr = Utils::trim(it->second);

    // 2) Extrai host e porta (suporta [IPv6]:port)
    std::string hostOnly = hostHdr;
    int reqPort = -1;
    if (!hostHdr.empty()) {
        if (hostHdr[0] == '[') {
            size_t rb = hostHdr.find(']');
            if (rb != std::string::npos) {
                hostOnly = hostHdr.substr(1, rb - 1);
                size_t colon = hostHdr.find(':', rb);
                if (colon != std::string::npos)
                    reqPort = std::atoi(hostHdr.c_str() + colon + 1);
            }
        } else {
            size_t colon = hostHdr.rfind(':');
            if (colon != std::string::npos) {
                reqPort = std::atoi(hostHdr.c_str() + colon + 1);
                hostOnly = hostHdr.substr(0, colon);
            }
        }
    }
    std::string hostLC = Utils::toLower(hostOnly);

    // 3) Candidatos (se porta informada, filtra por ela)
    std::vector<const ServerConfig*> cand;
    cand.reserve(_conf.servers.size());
    for (size_t i = 0; i < _conf.servers.size(); ++i) {
        const ServerConfig &s = _conf.servers[i];
        if (reqPort == -1 || s.port == reqPort)
            cand.push_back(&s);
    }
    if (cand.empty())
        return _conf.servers.empty()? (const ServerConfig*)0 : &_conf.servers[0];

    // 4) PRIMEIRO: match exato por hostname (case-insensitive)
    if (!hostLC.empty()) {
        for (size_t i = 0; i < cand.size(); ++i) {
            const ServerConfig *s = cand[i];
            for (size_t j = 0; j < s->server_names.size(); ++j) {
                if (Utils::toLower(s->server_names[j]) == hostLC)
                    return s;
            }
        }
    }

    // 5) DEPOIS: aceita wildcard "_" (apenas entre os candidatos)
    for (size_t i = 0; i < cand.size(); ++i) {
        const ServerConfig *s = cand[i];
        for (size_t j = 0; j < s->server_names.size(); ++j) {
            if (s->server_names[j] == "_")
                return s;
        }
    }

    // 6) Fallbacks
    for (size_t i = 0; i < cand.size(); ++i)
        if (cand[i]->is_default) return cand[i];

    return cand[0];
}


const LocationConfig* Router::pickLocation(const ServerConfig *srv, const std::string &uri) const {
    const LocationConfig *best = 0;
    size_t bestLen = 0;

    for (size_t i=0; i<srv->locations.size(); ++i) {
        const LocationConfig &loc = srv->locations[i];
        const std::string &p = loc.path;           // ex: "/cgi/", "/files/", "/"
        if (!Utils::startsWith(uri, p)) continue;

        // fronteira: evita "/cgi" casar "/cgiX"
        if (p != "/" && p.size() && p[p.size()-1] != '/' &&
            uri.size() > p.size() && uri[p.size()] != '/') continue;

        if (p.size() > bestLen) { best = &loc; bestLen = p.size(); }
    }
    return best;
}




// Router.cpp
RouteMatch Router::match(const HttpRequest &req) const {
    RouteMatch m;
    m.server = pickServer(req);
    if (!m.server) return m;

    m.loc = pickLocation(m.server, req.uri); // longest prefix

    // fsRoot = root da location se houver, senão do server
    m.fsRoot = m.server->root;
    if (m.loc && !m.loc->root.empty())
        m.fsRoot = m.loc->root;

    // relPath = URI inteira sem query e sem a barra inicial
    std::string rel = req.uri;
    size_t q = rel.find('?'); if (q != std::string::npos) rel.erase(q);
    if (!rel.empty() && rel[0]=='/') rel.erase(0,1);

    // Remova o prefixo da location de relPath APENAS se a location tiver root customizado
    if (m.loc && !m.loc->root.empty()) {
        std::string prefix = m.loc->path;
        if (!prefix.empty() && prefix[0] == '/') prefix.erase(0, 1);  // remove barra inicial do prefixo
        size_t prefixLen = prefix.size();
        if (prefixLen > 0 && Utils::startsWith(rel, prefix)) {
            rel.erase(0, prefixLen);  // remove o prefixo
        }
        // Se a URI original terminava com '/', e relPath ficou vazio, adicione uma barra vazia para diretórios
        if (rel.empty() && Utils::endsWith(req.uri, "/")) {
            rel = "";  // Mantenha vazio para diretórios raiz da location
        }
        if (!rel.empty() && rel[0] == '/') rel.erase(0, 1);  // remove barra residual se houver
    }

    m.relPath = rel;  // agora relPath é relativo ao root da location (ou server)
    return m;
}
