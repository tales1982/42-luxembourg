#include "Utils.hpp"

std::string getMimeType(const std::string& path) {
    size_t dot = path.rfind('.');
    if (dot == std::string::npos)
        return "text/plain";

    std::string ext = path.substr(dot + 1);
    if (ext == "html") return "text/html";
    if (ext == "css") return "text/css";
    if (ext == "js") return "application/javascript";
    if (ext == "png") return "image/png";
    if (ext == "jpg" || ext == "jpeg") return "image/jpeg";
    if (ext == "gif") return "image/gif";
    if (ext == "svg") return "image/svg+xml";
    if (ext == "json") return "application/json";
    if (ext == "ico") return "image/x-icon";
    return "application/octet-stream";
}
