#include "Server.hpp"
#include "DefaultErrorPage.hpp"
#include "Utils.hpp"
#include "AutoIndex.hpp"
#include "CGI.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <algorithm>
#include <sys/select.h>
#include <sys/stat.h>
#include <ctime>
#include <cstdio>
#include <sstream>
#include <vector>
#include <set>
#include <iostream>

// === Helpers locais p/ criar diretório recursivo e pegar nome de arquivo ===
static void ensureDir(const std::string &path)
{
	// cria recursivamente "a/b/c" com mkdir(0755)
	if (path.empty())
		return;
	std::string partial;
	partial.reserve(path.size());
	for (size_t i = 0; i < path.size(); ++i)
	{
		char ch = path[i];
		partial.push_back(ch);
		if (ch == '/' || i == path.size() - 1)
		{
			if (!partial.empty() && partial != "/" && partial != "./" && partial != ".")
			{
				struct stat st;
				if (stat(partial.c_str(), &st) != 0)
				{
					mkdir(partial.c_str(), 0755);
				}
			}
		}
	}
}

// retorna só o nome (remove diretórios) e sanitiza para evitar traversal
static std::string safeBaseName(std::string s)
{
	if (s.empty())
		return "";
	// remove tudo antes da última '/' ou '\\'
	size_t p = s.find_last_of("/\\");
	if (p != std::string::npos)
		s = s.substr(p + 1);

	// remove sequências perigosas e caracteres esquisitos
	std::string out;
	out.reserve(s.size());
	for (size_t i = 0; i < s.size(); ++i)
	{
		unsigned char c = static_cast<unsigned char>(s[i]);
		bool ok =
			(c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') ||
			c == '.' || c == '-' || c == '_';
		out.push_back(ok ? c : '_');
	}
	// evita nomes vazios ou '..'
	if (out.empty() || out == "." || out == "..")
		out = "file";
	return out;
}

// --- helper: pega apenas o path sem query, e remove a leading '/' para virar relativo ---
/* static std::string uriPathRel(const std::string &uri)
{
	size_t q = uri.find('?');
	std::string p = (q == std::string::npos) ? uri : uri.substr(0, q);
	if (!p.empty() && p[0] == '/')
		p.erase(0, 1);
	return p; // pode ser vazio -> root
} */
// Busca de header case-insensitive. Retorna "" se não achar.
static std::string getHeaderCI(const HttpRequest &req, const std::string &keyWanted)
{
	std::string want = Utils::toLower(keyWanted);
	for (std::map<std::string, std::string>::const_iterator it = req.headers.begin();
		 it != req.headers.end(); ++it)
	{
		if (Utils::toLower(it->first) == want)
			return it->second;
	}
	return "";
}

// Recorta "mime/type; charset=utf-8" -> "mime/type"
static std::string contentTypeBase(const std::string &ct)
{
	std::string s = Utils::toLower(ct);
	size_t p = s.find(';');
	if (p != std::string::npos)
		s.erase(p);
	Utils::trim(s);
	return s;
}

ServerApp::ServerApp(const GlobalConfig &conf) : _conf(conf), _router(_conf), _contentLimit(50 * 1024 * 1024) {}

void ServerApp::setNonBlocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void ServerApp::setupListeners()
{
	for (size_t i = 0; i < _conf.servers.size(); ++i)
	{
		int fd = socket(AF_INET, SOCK_STREAM, 0);
		if (fd < 0)
			continue;
		int opt = 1;
		setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

		struct sockaddr_in addr;
		std::memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(_conf.servers[i].port);
		addr.sin_addr.s_addr = inet_addr(_conf.servers[i].host.c_str());
		if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		{
			close(fd);
			continue;
		}
		if (listen(fd, 128) < 0)
		{
			close(fd);
			continue;
		}
		setNonBlocking(fd);
		_listenFDs.push_back(fd);
	}
}

void ServerApp::acceptNew(int lfd)
{
	struct sockaddr_in cli;
	socklen_t cl = sizeof(cli);
	int cfd = accept(lfd, (struct sockaddr *)&cli, &cl);
	if (cfd < 0)
		return;
	setNonBlocking(cfd);
	Connection c;
	c.fd = cfd;
	c.wantWrite = false;
	c.closeAfterWrite = false;
	c.hasRequest = false;
	c.boundServer = 0;
	_conns[cfd] = c;
}

void ServerApp::closeConn(int fd)
{
	std::map<int, Connection>::iterator it = _conns.find(fd);
	if (it != _conns.end())
	{
		close(fd);
		_conns.erase(it);
	}
}

// Função handleRead revisada
void ServerApp::handleRead(int fd) {
    char buf[8192];
    ssize_t n = recv(fd, buf, sizeof(buf), 0);

    // Fechar em EOF ou erro
    if (n == 0) {
        closeConn(fd);
        return;
    }
    if (n < 0) {
        closeConn(fd);
        return;
    }

    Connection &c = _conns[fd];
    std::string chunk(buf, n);
    size_t consumed = 0;

    // Tenta parsear o chunk recebido
    if (!c.hasRequest) {
        if (c.parser.parse(chunk, consumed, c.req, _contentLimit)) {
            c.hasRequest = true;

            // Verifica se o Content-Length excede o client_max_body_size do servidor
            const ServerConfig *srv = _router.match(c.req).server;
            if (srv) {
                size_t contentLen = 0;
                std::map<std::string, std::string>::const_iterator clIt = c.req.headers.find("Content-Length");
                if (clIt != c.req.headers.end()) {
                    contentLen = std::atoi(clIt->second.c_str());
                }
                if (contentLen > srv->client_max_body_size) {
                    HttpResponse res;
                    res.status = 413;
                    res.reason = httpStatusReason(413);
                    res.headers["Content-Length"] = "0";
                    res.headers["Content-Type"] = "text/plain";
                    queueResponse(c, res);
                    c.closeAfterWrite = true;
                    return;
                }
            }

            processRequest(c);
        }
        // Se o parse não completar, o parser mantém o estado internamente
        // e espera mais dados no próximo recv
    }
}

void ServerApp::handleWrite(int fd)
{
	Connection &c = _conns[fd];
	if (!c.outbuf.empty())
	{
		ssize_t n = send(fd, c.outbuf.c_str(), c.outbuf.size(), 0);
		if (n > 0)
			c.outbuf.erase(0, n);
		else if (n < 0)
		{
			closeConn(fd);
			return;
		} // <- importante p/ a defesa
	}
	if (c.outbuf.empty())
	{
		if (c.closeAfterWrite)
		{
			closeConn(fd);
			return;
		}
		c.wantWrite = false;
		c.hasRequest = false;
	}
}

HttpResponse ServerApp::handleStatic(const HttpRequest &req, const RouteMatch &rm)
{
	HttpResponse res;
	res.status = 200;
	res.reason = httpStatusReason(200);

	std::string uri = req.uri;
	size_t q = uri.find('?');
	if (q != std::string::npos)
		uri = uri.substr(0, q);

	std::string fsRel = rm.relPath; // já deveria vir relativo
	std::string fsPath = Utils::safePathJoin(rm.fsRoot, fsRel);

	if (Utils::isDir(fsPath))
	{
		// 1) tenta index da location (se houver)
		if (rm.loc && !rm.loc->index.empty() && Utils::fileExists(Utils::joinPath(fsPath, rm.loc->index)))
		{
			fsPath = Utils::joinPath(fsPath, rm.loc->index);
		}
		// 2) fallback: tenta "index.html" por padrão
		else if (Utils::fileExists(Utils::joinPath(fsPath, "index.html")))
		{
			fsPath = Utils::joinPath(fsPath, "index.html");
		}
		// 3) se a location permite autoindex, gera listing
		else if (rm.loc && rm.loc->autoindex)
		{
			res.headers["Content-Type"] = "text/html";
			res.body = AutoIndex::generate(req.uri, fsPath);
			return res;
		}
		// 4) caso contrário, sem index -> 403
		else
		{
			res.status = 403;
			res.reason = httpStatusReason(res.status);
			return res;
		}
	}

	if (!Utils::fileExists(fsPath))
	{
		res.status = 404;
		res.reason = httpStatusReason(404);
		return res;
	}

	res.headers["Content-Type"] = Utils::guessMime(fsPath);
	res.body = Utils::readFile(fsPath);
	return res;
}

HttpResponse ServerApp::handleUpload(const HttpRequest &req, const RouteMatch &rm)
{
	HttpResponse res;

	// precisa estar numa location com upload_on on;
	if (!rm.loc || !rm.loc->upload_on)
	{
		res.status = 403;
		res.reason = httpStatusReason(403);
		return res;
	}

	// diretório-alvo (padrão agora é ./data se não setado)
	std::string store = rm.loc->upload_store.empty() ? "./data" : rm.loc->upload_store;

	// garante que o diretório existe
	ensureDir(store);
	// conteúdo padrão é o body cru (aceita QUALQUER content-type)
	std::string payload = req.body;

	// Se for application/x-www-form-urlencoded, preserva comportamento antigo (campo "data")
	// Normaliza Content-Type (minúsculo, sem "; charset=...")
	std::string ctRaw = getHeaderCI(req, "Content-Type");
	std::string ctBase = contentTypeBase(ctRaw);

	// Se for application/x-www-form-urlencoded, preserva comportamento antigo (campo "data")
	if (ctBase == "application/x-www-form-urlencoded")
	{
		std::string s = payload;
		std::string val;
		size_t p = s.find("data=");
		if (p != std::string::npos)
		{
			val = s.substr(p + 5);
			size_t amp = val.find('&');
			if (amp != std::string::npos)
				val.erase(amp);
			payload = Utils::urlDecode(val);
		}
	}

	// nome do arquivo vindo do header X-Filename (enviado pelo front)
	std::string fname = getHeaderCI(req, "X-Filename");
	fname = safeBaseName(fname);

	if (fname.empty())
	{
		// Inferir extensão por MIME base
		std::string ext;
		if (ctBase == "application/pdf")
			ext = ".pdf";
		else if (ctBase == "image/jpeg")
			ext = ".jpg";
		else if (ctBase == "image/png")
			ext = ".png";
		else if (ctBase == "image/gif")
			ext = ".gif";
		else if (ctBase == "image/webp")
			ext = ".webp";
		else if (ctBase == "text/plain")
			ext = ".txt";
		else if (ctBase == "application/json")
			ext = ".json";
		else if (ctBase == "text/html")
			ext = ".html";
		else if (ctBase == "application/zip")
			ext = ".zip";
		else if (ctBase.empty())
			ext = ".bin";
		else
			ext = ".bin";

		fname = "upload_" + Utils::utoa((size_t)std::time(NULL)) + ext;
	}

	// caminho final
	std::string path = Utils::joinPath(store, fname);

	// grava bytes
	FILE *fp = std::fopen(path.c_str(), "wb");
	if (!fp)
	{
		res.status = 500;
		res.reason = httpStatusReason(500);
		return res;
	}
	if (!payload.empty())
		std::fwrite(payload.data(), 1, payload.size(), fp);
	std::fclose(fp);

	// resposta
	res.status = 201; // Created
	res.reason = httpStatusReason(201);
	res.headers["Content-Type"] = "text/plain";
	// Dica: devolve onde ficou disponível via /uploads/
	res.headers["Location"] = "/uploads/" + fname;
	res.body = "Saved as: " + path + "\n";

	std::cerr << "\033[35m[UPLOAD]\033[0m wrote " << payload.size()
			  << " bytes to " << path << "\n";
	return res;
}

HttpResponse ServerApp::handleDelete(const std::string &fsPath)
{
	HttpResponse res;
	if (!Utils::fileExists(fsPath))
	{
		res.status = 404;
		res.reason = httpStatusReason(404);
		return res;
	}
	if (unlink(fsPath.c_str()) != 0)
	{
		res.status = 403;
		res.reason = httpStatusReason(403);
		return res;
	}
	res.status = 204;
	res.reason = httpStatusReason(204);
	return res;
}
// Função processRequest revisada
void ServerApp::processRequest(Connection &c) {
    bool keepAlive = true;
    std::string conn = Utils::toLower(getHeaderCI(c.req, "Connection"));
    if (c.req.version == "HTTP/1.0" && conn != "keep-alive")
        keepAlive = false;
    if (c.req.version == "HTTP/1.1" && conn == "close")
        keepAlive = false;

    HttpRequest &req = c.req;
    RouteMatch rm = _router.match(req);
    const ServerConfig *srv = rm.server;
    if (!srv) {
        HttpResponse res;
        res.status = 500;
        res.reason = httpStatusReason(500);
        queueResponse(c, res);
        c.closeAfterWrite = true;
        return;
    }

    // Verifica se o Content-Length excede o client_max_body_size do servidor
    size_t contentLen = 0;
    std::map<std::string, std::string>::const_iterator clIt = req.headers.find("Content-Length");
    if (clIt != req.headers.end()) {
        contentLen = std::atoi(clIt->second.c_str());
    }
    if (contentLen > srv->client_max_body_size) {
        HttpResponse res;
        res.status = 413;
        res.reason = httpStatusReason(413);
        res.headers["Content-Length"] = "0";
        res.headers["Content-Type"] = "text/plain";
        queueResponse(c, res);
        c.closeAfterWrite = true;
        return;
    }

    // Redirect (se configurado na location)
    if (rm.loc && !rm.loc->redirect.empty()) {
        HttpResponse res;
        size_t sp = rm.loc->redirect.find(' ');
        if (sp == std::string::npos) {
            res.status = 500;
            res.reason = httpStatusReason(500);
        } else {
            std::string code = rm.loc->redirect.substr(0, sp);
            res.status = std::atoi(code.c_str());
            res.reason = httpStatusReason(res.status);
            res.headers["Location"] = rm.loc->redirect.substr(sp + 1);
        }
        queueResponse(c, res);
        c.closeAfterWrite = true;
        return;
    }

    // Retira do match — REMOVENDO a query do relPath
    std::string relNoQ = rm.relPath;
    size_t qpos = relNoQ.find('?');
    if (qpos != std::string::npos)
        relNoQ.erase(qpos);

    std::string fsPath = Utils::safePathJoin(rm.fsRoot, relNoQ);

    // DEBUG: caminho real calculado para o CGI/estático
    std::cerr << "\033[33m[CGI-DEBUG]\033[0m fsRoot=" << rm.fsRoot
              << " relPath=" << rm.relPath
              << " (noQ=" << relNoQ << ")"
              << " -> fsPath=" << fsPath << std::endl;

    // CGI
    if (rm.loc && CGI::isCGI(rm.loc, rm.relPath)) {
        HttpResponse res = CGI::run(req, rm, fsPath); // fsPath do script real
        queueResponse(c, res);
        c.closeAfterWrite = !keepAlive;
        return;
    }

    // OPTIONS (preflight CORS + Allow)
    if (req.method == "OPTIONS") {
        HttpResponse res;
        res.status = 204; // No Content
        res.reason = httpStatusReason(204);

        // Monte o Allow a partir da location (ou padrão GET, HEAD)
        std::string allow = "GET, HEAD";
        if (rm.loc && !rm.loc->methods.empty()) {
            std::set<std::string> allowSet(rm.loc->methods.begin(), rm.loc->methods.end());
            bool first = true;
            std::ostringstream oss;
            for (std::set<std::string>::const_iterator it = allowSet.begin(); it != allowSet.end(); ++it) {
                if (!first) oss << ", ";
                oss << *it;
                first = false;
            }
            if (allowSet.count("GET") && !allowSet.count("HEAD"))
                oss << ", HEAD";
            allow = oss.str();
        }
        res.headers["Allow"] = allow;

        // CORS “liberal” o suficiente pro teu UI
        res.headers["Access-Control-Allow-Origin"] = "*";
        res.headers["Access-Control-Allow-Methods"] = allow;
        res.headers["Access-Control-Allow-Headers"] = "Content-Type, X-Filename";
        res.headers["Access-Control-Max-Age"] = "600";
        res.headers["Content-Length"] = "0";
        res.headers["Connection"] = "close";

        queueResponse(c, res);
        c.closeAfterWrite = true;
        return;
    }

    // GET / HEAD (HEAD tratado no queueResponse)
    if (req.method == "GET" || req.method == "HEAD") {
        HttpResponse res = handleStatic(req, rm);
        queueResponse(c, res);
        c.closeAfterWrite = !keepAlive;
        return;
    }

    // POST
    if (req.method == "POST") {
        // Log de depuração útil para POST
        std::cerr << "\033[35m[POST-DEBUG]\033[0m uri=" << req.uri
                  << " matched_loc=" << (rm.loc ? rm.loc->path : "<none>")
                  << " methods=";

        if (rm.loc) {
            for (size_t i = 0; i < rm.loc->methods.size(); ++i)
                std::cerr << rm.loc->methods[i] << " ";
        }

        std::cerr << " ctBase=" << contentTypeBase(getHeaderCI(req, "Content-Type"))
                  << " x-filename=" << getHeaderCI(req, "X-Filename")
                  << "\n";

        // Segurança extra: garanta que rm.loc existe antes de acessar
        if (rm.loc && rm.loc->upload_on) {
            HttpResponse res = handleUpload(req, rm);
            queueResponse(c, res);
            c.closeAfterWrite = !keepAlive;
            return;
        }

        // POST permitido mas não é upload (nem CGI, que foi tratado acima) -> sirva estático
        HttpResponse res = handleStatic(req, rm);
        queueResponse(c, res);
        c.closeAfterWrite = !keepAlive;
        return;
    }

    // DELETE
    if (req.method == "DELETE") {
        HttpResponse res = handleDelete(fsPath);
        queueResponse(c, res);
        c.closeAfterWrite = !keepAlive;
        return;
    }

    // Qualquer outro método -> 405
    HttpResponse res;
    res.status = 405;
    res.reason = httpStatusReason(405);

    if (rm.loc && !rm.loc->methods.empty()) {
        std::set<std::string> allowSet(rm.loc->methods.begin(), rm.loc->methods.end());
        std::ostringstream oss;
        for (std::set<std::string>::const_iterator it = allowSet.begin(); it != allowSet.end(); ++it) {
            if (it != allowSet.begin())
                oss << ", ";
            oss << *it;
        }
        res.headers["Allow"] = oss.str();
    } else {
        // raiz sem location -> apenas GET anunciado
        res.headers["Allow"] = "GET";
    }

    res.headers["Content-Length"] = "0";
    res.headers["Content-Type"] = "text/plain";

    queueResponse(c, res);
    c.closeAfterWrite = !keepAlive;
}

std::string ServerApp::buildResponse(const HttpResponse &res, bool keepAlive)
{
	HttpResponse out = res;

	// Reason padrão
	if (out.reason.empty())
		out.reason = httpStatusReason(out.status);

	// Content-Type padrão se houver corpo
	if (!out.body.empty() && out.headers.find("Content-Type") == out.headers.end())
		out.headers["Content-Type"] = "text/html; charset=utf-8";

	// Cabeçalhos padrão
	out.headers["Date"] = Utils::getTimeRfc1123();
	out.headers["Server"] = "webserv/42";
	if (out.headers.find("Connection") == out.headers.end())
	{
		out.headers["Connection"] = keepAlive ? "keep-alive" : "close";
	}

	// ---- Desativar cache por padrão ----
	// Se não tiverem sido definidos explicitamente, força no-cache/no-store
	if (out.headers.find("Cache-Control") == out.headers.end())
	{
		out.headers["Cache-Control"] = "no-store, no-cache, must-revalidate, max-age=0";
		out.headers["Pragma"] = "no-cache";
		out.headers["Expires"] = "0";
	}

	// *** Regras de corpo/Content-Length por status ***
	// 1xx / 204 / 304 --> sem corpo e Content-Length: 0
	if ((out.status >= 100 && out.status < 200) || out.status == 204 || out.status == 304)
	{
		out.body.clear();
		out.headers["Content-Length"] = "0";
	}
	// Para os demais, respeita Content-Length pré-definido (ex.: HEAD);
	// caso contrário, calcula a partir do body atual.
	else if (out.headers.find("Content-Length") == out.headers.end())
	{
		out.headers["Content-Length"] = Utils::utoa(out.body.size());
	}

	// Monta a resposta
	std::ostringstream oss;
	oss << "HTTP/1.1 " << out.status << " " << out.reason << "\r\n";
	for (std::map<std::string, std::string>::const_iterator it = out.headers.begin();
		 it != out.headers.end(); ++it)
	{
		oss << it->first << ": " << it->second << "\r\n";
	}
	oss << "\r\n";
	oss << out.body; // em HEAD o body já foi limpo antes de chegar aqui
	return oss.str();
}

void ServerApp::queueResponse(Connection &c, const HttpResponse &res)
{
	bool keepAlive = true;
	std::string conn = Utils::toLower(getHeaderCI(c.req, "Connection"));

	if (c.req.version == "HTTP/1.0" && conn != "keep-alive")
		keepAlive = false;
	if (c.req.version == "HTTP/1.1" && conn == "close")
		keepAlive = false;

	HttpResponse final = res;
	final.headers["Connection"] = "close";

	std::map<std::string, std::string>::const_iterator itConn = final.headers.find("Connection");
	if (itConn != final.headers.end() && Utils::toLower(itConn->second) == "close")
	{
		keepAlive = false;
	}

	const ServerConfig *srv = _router.match(c.req).server;
	bool suppressErrorBody = (final.headers.count("Content-Length") > 0);

	// 1) Usa error_page customizada se houver e for erro
	/* if ((final.status >= 400) && srv && srv->error_pages.count(final.status))
	{
		std::string ep = srv->error_pages.find(final.status)->second;
		std::string body = Utils::readFile(ep);
		if (!body.empty())
		{
			final.body = body;
			final.headers["Content-Type"] = "text/html";
		}
	} */

	// 1) Usa error_page customizada se houver e for erro
	if (!suppressErrorBody && (final.status >= 400) && srv && srv->error_pages.count(final.status))
	{
		std::string ep = srv->error_pages.find(final.status)->second;
		std::string body = Utils::readFile(ep);
		if (!body.empty())
		{
			final.body = body;
			final.headers["Content-Type"] = "text/html";
		}
	}

	// 2) Fallback: erro sem corpo e sem error_page -> HTML padrão
	/* 	if (final.status >= 400 && final.body.empty() &&
			!(srv && srv->error_pages.count(final.status)))
		{
			final.body = generateDefaultErrorHtml(final.status);
			final.headers["Content-Type"] = "text/html; charset=utf-8";
		} */

	if (!suppressErrorBody &&
		final.status >= 400 && final.body.empty() &&
		!(srv && srv->error_pages.count(final.status)))
	{
		final.body = generateDefaultErrorHtml(final.status);
		final.headers["Content-Type"] = "text/html; charset=utf-8";
	}

	// 3) HEAD: manter Content-Length do corpo real, mas não enviar corpo
	if (Utils::toLower(c.req.method) == "head")
	{
		if (final.headers.find("Content-Length") == final.headers.end())
		{
			final.headers["Content-Length"] = Utils::utoa(final.body.size());
		}
		final.body.clear();
	}

	// 4) Monta e agenda a escrita
	c.outbuf = buildResponse(final, keepAlive);
	c.wantWrite = true;
	c.closeAfterWrite = !keepAlive;

	// 5) (Opcional) Log por resposta com ANSI
	const char *GREEN = "\033[32m";
	const char *YELLOW = "\033[33m";
	const char *CYAN = "\033[36m";
	const char *RESET = "\033[0m";

	std::cerr << CYAN << "[RESP] " << RESET
			  << Utils::toUpper(c.req.method) << " "
			  << c.req.uri << " -> "
			  << (final.status >= 400 ? YELLOW : GREEN)
			  << final.status << RESET
			  << " (keepAlive=" << (keepAlive ? "true" : "false") << ")\n";
}

void ServerApp::run()
{
	setupListeners();

	while (true)
	{
		fd_set rfds, wfds;
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);
		int maxfd = 0;

		for (size_t i = 0; i < _listenFDs.size(); ++i)
		{
			FD_SET(_listenFDs[i], &rfds);
			if (_listenFDs[i] > maxfd)
				maxfd = _listenFDs[i];
		}
		for (std::map<int, Connection>::iterator it = _conns.begin(); it != _conns.end(); ++it)
		{
			FD_SET(it->first, &rfds);
			if (it->second.wantWrite)
				FD_SET(it->first, &wfds);
			if (it->first > maxfd)
				maxfd = it->first;
		}

		struct timeval tv;
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		int r = select(maxfd + 1, &rfds, &wfds, 0, &tv);
		(void)r;

		for (size_t i = 0; i < _listenFDs.size(); ++i)
		{
			if (FD_ISSET(_listenFDs[i], &rfds))
				acceptNew(_listenFDs[i]);
		}

		std::vector<int> toWrite;
		std::vector<int> toRead;
		for (std::map<int, Connection>::iterator it = _conns.begin(); it != _conns.end(); ++it)
		{
			int fd = it->first;
			if (FD_ISSET(fd, &rfds))
				toRead.push_back(fd);
			if (FD_ISSET(fd, &wfds))
				toWrite.push_back(fd);
		}
		for (size_t i = 0; i < toRead.size(); ++i)
		{
			if (_conns.find(toRead[i]) != _conns.end())
				handleRead(toRead[i]);
		}
		for (size_t i = 0; i < toWrite.size(); ++i)
		{
			if (_conns.find(toWrite[i]) != _conns.end())
				handleWrite(toWrite[i]);
		}
	}
}
