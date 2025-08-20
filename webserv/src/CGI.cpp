#include "CGI.hpp"
#include "Utils.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>

extern char **environ;

namespace CGI {

bool isCGI(const LocationConfig *loc, const std::string &path) {
    if (!loc) return false;
    if (loc->cgi_ext.empty()) return false;
    return Utils::endsWith(path, loc->cgi_ext);
}

static void setEnv(const std::string &k, const std::string &v) {
    setenv(k.c_str(), v.c_str(), 1);
}

HttpResponse run(const HttpRequest &req, const RouteMatch &rm, const std::string &fsPath) {
    HttpResponse res;
    res.status = 200;
    res.reason = httpStatusReason(200);

    int inpipe[2], outpipe[2];
    if (pipe(inpipe) == -1 || pipe(outpipe) == -1) {
        res.status = 500; res.reason = httpStatusReason(500);
        res.headers["Content-Type"] = "text/plain";
        res.body = "CGI: pipe() failed\n";
        return res;
    }

    pid_t pid = fork();
    if (pid < 0) {
        close(inpipe[0]); close(inpipe[1]);
        close(outpipe[0]); close(outpipe[1]);
        res.status = 500; res.reason = httpStatusReason(500);
        res.headers["Content-Type"] = "text/plain";
        res.body = "CGI: fork() failed\n";
        return res;
    }

    if (pid == 0) {
        // ----- child -----
        dup2(inpipe[0], 0);   // stdin  <- inpipe[0]
        dup2(outpipe[1], 1);  // stdout -> outpipe[1]
        close(inpipe[1]);
        close(outpipe[0]);

        // ENV CGI
        std::string qs;
        size_t qpos = req.uri.find('?');
        if (qpos != std::string::npos) qs = req.uri.substr(qpos + 1);

        setEnv("GATEWAY_INTERFACE", "CGI/1.1");
        setEnv("SERVER_PROTOCOL",  "HTTP/1.1");
        setEnv("REQUEST_METHOD",   req.method);
        setEnv("QUERY_STRING",     qs);
        setEnv("SCRIPT_FILENAME",  fsPath);
        if (req.headers.count("Content-Type"))
            setEnv("CONTENT_TYPE", req.headers.find("Content-Type")->second);
        setEnv("CONTENT_LENGTH",   Utils::utoa(req.body.size()));

        // Interpretador (python por padrão)
        std::string exec = (rm.loc && !rm.loc->cgi_executor.empty())
                         ? rm.loc->cgi_executor
                         : "/usr/bin/python3";

        // chdir para a pasta do script + usar apenas o basename no argv
        size_t slash = fsPath.find_last_of('/');
        std::string dir  = (slash == std::string::npos) ? "." : fsPath.substr(0, slash);
        std::string base = (slash == std::string::npos) ? fsPath : fsPath.substr(slash + 1);
        chdir(dir.c_str());

        std::vector<char*> argv;
        argv.push_back(const_cast<char*>(exec.c_str()));
        argv.push_back(const_cast<char*>(base.c_str()));  // ex.: "echo.py"
        argv.push_back(NULL);

        execve(exec.c_str(), &argv[0], environ);
        _exit(127); // se exec falhar
    }

    // ----- parent -----
    close(inpipe[0]);   // pai escreve no stdin do CGI
    close(outpipe[1]);  // pai lê stdout do CGI

    if (!req.body.empty()) {
        (void)write(inpipe[1], req.body.data(), req.body.size());
    }
    close(inpipe[1]);

    std::string out;
    char buf[4096];
    ssize_t n;
    while ((n = read(outpipe[0], buf, sizeof(buf))) > 0) {
        out.append(buf, n);
    }
    close(outpipe[0]);

    int status = 0;
    waitpid(pid, &status, 0);

    // Se o script terminou com erro, devolve 502
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        res.status = 502;
        res.reason = httpStatusReason(502);
        res.headers["Content-Type"] = "text/plain";
        res.body = "Bad Gateway (CGI failed)\n";
        return res;
    }

    // Parse dos headers do CGI
    size_t sep = out.find("\r\n\r\n");
    size_t adv = 4;
    if (sep == std::string::npos) { sep = out.find("\n\n"); adv = 2; }

    std::map<std::string, std::string> hdrs;
    std::string body;

    if (sep != std::string::npos) {
        std::string rawh = out.substr(0, sep);
        body = out.substr(sep + adv);

        std::istringstream hs(rawh);
        std::string line;
        while (std::getline(hs, line)) {
            if (!line.empty() && line[line.size()-1] == '\r')
                line.erase(line.size()-1);

            size_t c = line.find(':');
            if (c != std::string::npos) {
                std::string k = line.substr(0, c);
                std::string v = Utils::trim(line.substr(c + 1));
                hdrs[k] = v;
            } else if (Utils::startsWith(line, "Status")) {
                // ex.: "Status: 200 OK" ou "Status 200 OK"
                size_t sp = line.find(' ');
                if (sp != std::string::npos) {
                    int code = std::atoi(line.c_str() + sp + 1);
                    if (code >= 100 && code < 1000) {
                        res.status = code;
                        res.reason = httpStatusReason(code);
                    }
                }
            }
        }
    } else {
        body = out; // sem headers, tudo é body
    }

    res.body = body;

    // Status via header "Status:"
    if (hdrs.find("Status") != hdrs.end()) {
        int code = std::atoi(hdrs["Status"].c_str());
        if (code >= 100 && code < 1000) {
            res.status = code;
            res.reason = httpStatusReason(code);
        }
        hdrs.erase("Status");
    }

    // Content-Type default
    if (hdrs.find("Content-Type") != hdrs.end())
        res.headers["Content-Type"] = hdrs["Content-Type"];
    else
        res.headers["Content-Type"] = "text/plain";

    return res;
}

} // namespace CGI
