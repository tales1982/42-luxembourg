/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:20:01 by tales             #+#    #+#             */
/*   Updated: 2025/09/01 09:20:02 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"
#include "Utils.hpp"
#include "CGIManager.hpp"

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

namespace CGI
{

    bool isCGI(const LocationConfig *loc, const std::string &path)
    {
        if (!loc || loc->cgi_ext.empty())
            return false;
        std::string ext = loc->cgi_ext;
        if (ext[0] != '.')
            ext = "." + ext;               
        return Utils::endsWith(path, ext); 
    }

    HttpResponse run(const HttpRequest &req,
                     const RouteMatch &rm,
                     const std::string &fsPath)
    {
        HttpResponse res;

        // Build CGI environment
        std::map<std::string, std::string> env;

        std::string qs;
        size_t qpos = req.uri.find('?');
        if (qpos != std::string::npos)
            qs = req.uri.substr(qpos + 1);

        // Variáveis CGI básicas
        env["GATEWAY_INTERFACE"] = "CGI/1.1";
        env["SERVER_PROTOCOL"] = "HTTP/1.1";
        env["REQUEST_METHOD"] = req.method;
        env["QUERY_STRING"] = qs; 
        env["SCRIPT_FILENAME"] = fsPath;

        // Cabeçalhos de corpo
        if (req.headers.count("Content-Type"))
            env["CONTENT_TYPE"] = req.headers.find("Content-Type")->second;
        env["CONTENT_LENGTH"] = Utils::utoa(req.body.size());

        // Extras úteis
        env["SERVER_NAME"] = "webserv";
        env["SERVER_PORT"] = "8080";
        env["SCRIPT_NAME"] = rm.relPath;
        env["PATH_INFO"] = "";

// IP do cliente (se não tiver no HttpRequest, use um fallback temporário)
#ifdef HAS_CLIENT_ADDR
        env["REMOTE_ADDR"] = req.clientAddr;
#else
        env["REMOTE_ADDR"] = "127.0.0.1";
#endif


        std::string exec = (rm.loc && !rm.loc->cgi_executor.empty())
                               ? rm.loc->cgi_executor
                               : "/usr/bin/python3";

        CgiResult r = CGIManager::run(
            exec, fsPath, env, req.body,
            5000,            // timeout em ms (ajuste se quiser)
            10 * 1024 * 1024 // limite de saída (10 MB)
        );

        if (r.timedOut || r.exitStatus == -1)
        {
            res.status = 504; // Gateway Timeout
            res.reason = httpStatusReason(res.status);
            res.headers["Content-Type"] = "text/plain";
            res.body = "Gateway Timeout (CGI)\n";
            return res;
        }

        // separa headers/body 
        std::string headers = r.rawHeaders;
        std::string body = r.body;
        if (headers.empty())
        {
            std::string combined = r.body;
            size_t p = combined.find("\r\n\r\n");
            size_t adv = 4;
            if (p == std::string::npos)
            {
                p = combined.find("\n\n");
                adv = 2;
            }
            if (p != std::string::npos)
            {
                headers = combined.substr(0, p);
                body = combined.substr(p + adv);
            }
            else
            {
                headers.clear();
                body = combined;
            }
        }

        int status = 200;
        std::map<std::string, std::string> hdrs;
        if (!headers.empty())
        {
            std::istringstream hs(headers);
            std::string line;
            while (std::getline(hs, line))
            {
                if (!line.empty() && line[line.size() - 1] == '\r')
                    line.erase(line.size() - 1);
                size_t c = line.find(':');
                if (c != std::string::npos)
                {
                    std::string k = line.substr(0, c);
                    std::string v = Utils::trim(line.substr(c + 1));
                    hdrs[k] = v;
                }
                else if (Utils::startsWith(line, "Status"))
                {
                    size_t sp = line.find(' ');
                    if (sp != std::string::npos)
                        status = std::atoi(line.c_str() + sp + 1);
                }
            }
            hdrs.erase("Status");
        }

        res.status = status;
        res.reason = httpStatusReason(res.status);
        res.body = body;
        res.headers["Content-Type"] =
            (hdrs.find("Content-Type") != hdrs.end()) ? hdrs["Content-Type"] : "text/plain";


        return res;
    }

} 
