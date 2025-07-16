// src/server/ResponseBuilder.cpp
#include "../../include/server/ResponseBuilder.hpp"
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>

std::string read_file(const std::string &path) {
    std::ifstream file(path.c_str(), std::ios::in | std::ios::binary);
    if (!file.is_open()) return "";
    std::ostringstream buf;
    buf << file.rdbuf();
    return buf.str();
}

std::string get_mime_type(const std::string &path) {
    if (path.find(".html")  != std::string::npos) return "text/html";
    if (path.find(".jpg")   != std::string::npos ||
        path.find(".jpeg")  != std::string::npos) return "image/jpeg";
    if (path.find(".png")   != std::string::npos) return "image/png";
    if (path.find(".css")   != std::string::npos) return "text/css";
    if (path.find(".js")    != std::string::npos) return "application/javascript";
    if (path.find(".pdf")   != std::string::npos) return "application/pdf";
    return "application/octet-stream";
}

std::string replace_placeholder(std::string source,
                                const std::string &ph,
                                const std::string &value) {
    size_t pos = source.find(ph);
    if (pos != std::string::npos) {
        source.replace(pos, ph.length(), value);
    }
    return source;
}

std::string generate_autoindex(const std::string &dirPath,
                               const std::string &urlPath) {
    DIR *d = opendir(dirPath.c_str());
    if (!d) return "";
    std::ostringstream list;
    struct dirent *e;
    while ((e = readdir(d)) != NULL) {
        std::string name = e->d_name;
        if (name == "." || name == "..") continue;
        list << "<li><a href=\"" << name << "\">" << name << "</a></li>\n";
    }
    closedir(d);
    std::string tmpl = read_file("www/autoindex_template.html");
    tmpl = replace_placeholder(tmpl, "{{PATH}}", urlPath);
    tmpl = replace_placeholder(tmpl, "{{LIST}}", list.str());
    return tmpl;
}

std::string generate_all_uploads_page() {
    std::ostringstream combo;
    const char *folders[] = {"./www/fotos/", "./www/pdfs/", "./www/othes/"};
    const char *routes[]  = {"/fotos/", "/pdfs/", "/othes/"};
    for (int i = 0; i < 3; ++i) {
        DIR *d = opendir(folders[i]);
        if (!d) continue;
        struct dirent *e;
        while ((e = readdir(d)) != NULL) {
            std::string name = e->d_name;
            if (name == "." || name == "..") continue;
            combo << "<li><a href=\"" << routes[i] << name << "\">" << name
                  << "</a></li>\n";
        }
        closedir(d);
    }
    std::string tmpl = read_file("www/all_uploads_template.html");
    tmpl = replace_placeholder(tmpl, "{{PATH}}", "/all-uploads");
    tmpl = replace_placeholder(tmpl, "{{LIST}}", combo.str());
    return tmpl;
}
