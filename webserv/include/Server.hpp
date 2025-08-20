#ifndef SERVER_HPP
#define SERVER_HPP

#include "Config.hpp"
#include "Http.hpp"
#include "Router.hpp"
#include <string>
#include <map>
#include <vector>
#include <cstdio>

struct Connection {
	int fd;
	std::string inbuf;
	std::string outbuf;
	bool wantWrite;
	bool closeAfterWrite;
	HttpParser parser;
	bool hasRequest;
	HttpRequest req;
	const ServerConfig *boundServer;
	Connection(): fd(-1), wantWrite(false), closeAfterWrite(false), hasRequest(false), boundServer(0) {}
};

class ServerApp {
public:
	ServerApp(const GlobalConfig &conf);
	void run();
private:
	GlobalConfig _conf;
	Router _router;
	std::vector<int> _listenFDs;
	std::map<int, Connection> _conns;
	size_t _contentLimit;

	void setupListeners();
	void setNonBlocking(int fd);
	void acceptNew(int lfd);
	void closeConn(int fd);
	void handleRead(int fd);
	void handleWrite(int fd);
	void processRequest(Connection &c);
	HttpResponse handleStatic(const HttpRequest &req, const RouteMatch &rm);
	HttpResponse handleUpload(const HttpRequest &req, const RouteMatch &rm);
	HttpResponse handleDelete(const std::string &fsPath);
	void queueResponse(Connection &c, const HttpResponse &res);
	std::string buildResponse(const HttpResponse &res, bool keepAlive);
};

#endif
