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

// --- helper: pega apenas o path sem query, e remove a leading '/' para virar relativo ---
static std::string uriPathRel(const std::string &uri)
{
	size_t q = uri.find('?');
	std::string p = (q == std::string::npos) ? uri : uri.substr(0, q);
	if (!p.empty() && p[0] == '/')
		p.erase(0, 1);
	return p; // pode ser vazio -> root
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

void ServerApp::handleRead(int fd)
{
	char buf[8192];
	ssize_t n = recv(fd, buf, sizeof(buf), 0);

	// Fechar em EOF ou erro
	if (n == 0)
	{
		closeConn(fd);
		return;
	}
	if (n < 0)
	{
		closeConn(fd);
		return;
	}

	Connection &c = _conns[fd];
	std::string chunk(buf, n);

	// Tenta parse direto do chunk (fast-path)
	size_t consumed = 0;
	if (!c.hasRequest)
	{
		if (c.parser.parse(chunk, consumed, c.req, _contentLimit))
		{
			c.hasRequest = true;
			processRequest(c);
			return;
		}

		// Se não deu, acumula no inbuf e tenta de novo (requisição parcial)
		c.inbuf += chunk;

		// Guarda rápida: se acumulou demais, responde 413 e evita estourar memória
		if (c.inbuf.size() > _contentLimit)
		{
			HttpResponse res;
			res.status = 413;
			res.reason = httpStatusReason(413);
			queueResponse(c, res);
			c.closeAfterWrite = true;
			c.inbuf.clear();
			return;
		}

		size_t dummy = 0;
		HttpRequest tmp;
		if (c.parser.parse(c.inbuf, dummy, tmp, _contentLimit))
		{
			c.req = tmp;
			c.hasRequest = true;
			c.inbuf.clear();
			processRequest(c);
			return;
		}
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

	// diretório-alvo
	std::string store = rm.loc->upload_store.empty() ? "./www/uploads" : rm.loc->upload_store;

	// nome simples (timestamp) — suficiente pro exercício
	std::string name = "upload_" + Utils::utoa((size_t)std::time(NULL)) + ".dat";
	std::string path = Utils::joinPath(store, name);

	// conteúdo padrão é o body cru
	std::string payload = req.body;

	// Se for application/x-www-form-urlencoded, salve o campo "data"
	std::map<std::string, std::string>::const_iterator ct = req.headers.find("Content-Type");
	if (ct != req.headers.end() && Utils::startsWith(Utils::toLower(ct->second), "application/x-www-form-urlencoded"))
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

	// grava o arquivo
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

	// resposta do upload
	res.status = 201; // Created
	res.reason = httpStatusReason(201);
	res.headers["Content-Type"] = "text/plain";
	res.body = "Saved as: " + path + "\n";

	// log opcional
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

void ServerApp::processRequest(Connection &c)
{
    HttpRequest &req = c.req;

    // --- NORMALIZAÇÃO DE URI: colapsa múltiplas barras ('//', '///', ...) para '/' ---
    {
        size_t q = req.uri.find('?');
        std::string path = (q == std::string::npos) ? req.uri : req.uri.substr(0, q);
        std::string qs   = (q == std::string::npos) ? ""      : req.uri.substr(q);

        std::string norm;
        norm.reserve(path.size());
        bool lastSlash = false;
        for (size_t i = 0; i < path.size(); ++i)
        {
            char ch = path[i];
            if (ch == '/')
            {
                if (!lastSlash) norm.push_back('/');
                lastSlash = true;
            }
            else
            {
                norm.push_back(ch);
                lastSlash = false;
            }
        }
        if (norm.empty()) norm = "/";
        req.uri = norm + qs;
    }
    // -------------------------------------------------------------------------------

    bool keepAlive = true;
    std::string conn = "";
    if (req.headers.count("Connection"))
        conn = Utils::toLower(req.headers["Connection"]);
    if (req.version == "HTTP/1.0" && conn != "keep-alive") keepAlive = false;
    if (req.version == "HTTP/1.1" && conn == "close")      keepAlive = false;

    // Primeiro matching por Router
    RouteMatch rm = _router.match(req);

    // Fallback se Router não encontrou server (ex: Host não bate com server_name)
    if (!rm.server)
    {
        if (_conf.servers.empty())
        {
            HttpResponse res;
            res.status = 500;
            res.reason = httpStatusReason(500);
            queueResponse(c, res);
            c.closeAfterWrite = true;
            return;
        }
        // monta um match mínimo contra o primeiro server configurado
        rm.server  = &_conf.servers[0];
        rm.loc     = NULL;                    // sem location específica
        rm.fsRoot  = rm.server->root;         // raiz do server
        rm.relPath = uriPathRel(req.uri);     // relativo a partir da raiz
    }

    // Root (sem location casada) aceita apenas GET/HEAD -> demais métodos: 405 + Allow: GET
    if (!rm.loc && req.method != "GET" && req.method != "HEAD")
    {
        HttpResponse res;
        res.status = 405;
        res.reason = httpStatusReason(405);
        res.headers["Allow"] = "GET";        // NÃO anuncie HEAD
        queueResponse(c, res);
        c.closeAfterWrite = !keepAlive;
        return;
    }

    // Limite de body em nível de servidor
    if (req.body.size() > rm.server->client_max_body_size)
    {
        HttpResponse res;
        res.status = 413;
        res.reason = httpStatusReason(413);
        queueResponse(c, res);
        c.closeAfterWrite = !keepAlive;
        return;
    }

    // métodos permitidos por location + header Allow em 405 (sem injetar HEAD no Allow)
    if (rm.loc && !rm.loc->methods.empty())
    {
        // HEAD é tratado como GET apenas para checagem de permissão
        std::string effMethod = req.method;
        if (effMethod == "HEAD") effMethod = "GET";

        std::set<std::string> allowSet(rm.loc->methods.begin(), rm.loc->methods.end());
        bool ok = allowSet.count(effMethod) > 0;

        if (!ok)
        {
            // Monta o header Allow APENAS com os métodos declarados na location
            std::ostringstream oss;
            for (std::set<std::string>::const_iterator it = allowSet.begin(); it != allowSet.end(); ++it)
            {
                if (it != allowSet.begin()) oss << ", ";
                oss << *it;
            }
            HttpResponse res;
            res.status = 405;
            res.reason = httpStatusReason(405);
            res.headers["Allow"] = oss.str(); // ex.: "GET" ou "GET, POST"
            queueResponse(c, res);
            c.closeAfterWrite = !keepAlive;
            return;
        }
    }

    // redirect por location
    if (rm.loc && !rm.loc->redirect.empty())
    {
        HttpResponse res;
        res.status = 301;
        res.reason = httpStatusReason(301);
        std::string code  = rm.loc->redirect.substr(0, rm.loc->redirect.find(' '));
        int ccode = std::atoi(code.c_str());
        if (ccode >= 300 && ccode < 400)
        {
            res.status = ccode;
            res.reason = httpStatusReason(ccode);
        }
        std::string target = rm.loc->redirect.substr(rm.loc->redirect.find(' ') + 1);
        res.headers["Location"] = target;
        queueResponse(c, res);
        c.closeAfterWrite = !keepAlive;
        return;
    }

    // Caminho de FS a partir do match — REMOVENDO a query do relPath
    std::string relNoQ = rm.relPath;
    size_t qpos = relNoQ.find('?');
    if (qpos != std::string::npos) relNoQ.erase(qpos);

    std::string fsPath = Utils::safePathJoin(rm.fsRoot, relNoQ);

    // DEBUG: caminho real calculado para o CGI/estático
    std::cerr << "\033[33m[CGI-DEBUG]\033[0m fsRoot=" << rm.fsRoot
              << " relPath=" << rm.relPath
              << " (noQ=" << relNoQ << ")"
              << " -> fsPath=" << fsPath << std::endl;

    // CGI
    if (rm.loc && CGI::isCGI(rm.loc, rm.relPath))
    {
        HttpResponse res = CGI::run(req, rm, fsPath); // fsPath do script real
        queueResponse(c, res);
        c.closeAfterWrite = !keepAlive;
        return;
    }

    // GET / HEAD (HEAD tratado no queueResponse)
    if (req.method == "GET" || req.method == "HEAD")
    {
        HttpResponse res = handleStatic(req, rm);
        queueResponse(c, res);
        c.closeAfterWrite = !keepAlive;
        return;
    }

    // POST
    if (req.method == "POST")
    {
        // se chegou aqui, rm.loc existe e POST é permitido pela checagem acima
        if (rm.loc->upload_on)
        {
            HttpResponse res = handleUpload(req, rm);
            queueResponse(c, res);
            c.closeAfterWrite = !keepAlive;
            return;
        }

        // POST permitido mas não é upload nem CGI -> trate como estático (se essa é a sua regra)
        HttpResponse res = handleStatic(req, rm);
        queueResponse(c, res);
        c.closeAfterWrite = !keepAlive;
        return;
    }

    // DELETE
    if (req.method == "DELETE")
    {
        HttpResponse res = handleDelete(fsPath);
        queueResponse(c, res);
        c.closeAfterWrite = !keepAlive;
        return;
    }

    // Qualquer outro método -> 405
    HttpResponse res;
    res.status = 405;
    res.reason = httpStatusReason(405);

    if (rm.loc && !rm.loc->methods.empty())
    {
        std::set<std::string> allowSet(rm.loc->methods.begin(), rm.loc->methods.end());
        std::ostringstream oss;
        for (std::set<std::string>::const_iterator it = allowSet.begin(); it != allowSet.end(); ++it)
        {
            if (it != allowSet.begin()) oss << ", ";
            oss << *it;
        }
        res.headers["Allow"] = oss.str();
    }
    else
    {
        // raiz sem location -> apenas GET anunciado
        res.headers["Allow"] = "GET";
    }

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
	out.headers["Connection"] = keepAlive ? "keep-alive" : "close";

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
	std::string conn = "";
	if (c.req.headers.count("Connection"))
		conn = Utils::toLower(c.req.headers["Connection"]);
	if (c.req.version == "HTTP/1.0" && conn != "keep-alive")
		keepAlive = false;
	if (c.req.version == "HTTP/1.1" && conn == "close")
		keepAlive = false;

	HttpResponse final = res;
	const ServerConfig *srv = _router.match(c.req).server;

	// 1) Usa error_page customizada se houver e for erro
	if ((final.status >= 400) && srv && srv->error_pages.count(final.status))
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
	if (final.status >= 400 && final.body.empty() &&
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
