#ifndef CGI_HPP
#define CGI_HPP

#include "Http.hpp"
#include "Router.hpp"
#include <string>

namespace CGI {
    bool isCGI(const LocationConfig *loc, const std::string &path);
    HttpResponse run(const HttpRequest &req,
                     const RouteMatch &rm,
                     const std::string &fsPath);
}

#endif
