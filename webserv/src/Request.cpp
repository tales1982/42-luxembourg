//src/Request.cpp
#include "Request.hpp"
#include <sstream>
#include <iostream>

Request::Request(const std::string& rawRequest) {
    parse(rawRequest);
}

void Request::parse(const std::string& raw) {
    std::istringstream stream(raw);
    std::string line;

    // First line: METHOD PATH VERSION
    if (std::getline(stream, line)) {
        std::istringstream firstLine(line);
        firstLine >> _method >> _path >> _version;
    }

    // Remaining lines: headers
    while (std::getline(stream, line) && line != "\r") {
        size_t colon = line.find(':');
        if (colon != std::string::npos) {
            std::string key = line.substr(0, colon);
            std::string value = line.substr(colon + 1);
            // Trim spaces
            if (!value.empty() && value[0] == ' ')
                value.erase(0, 1);
            if (!value.empty() && value[value.size()-1] == '\r')
                value.erase(value.size()-1);
            _headers[key] = value;
        }
    }
}

const std::string& Request::getMethod() const {
    return _method;
}

const std::string& Request::getPath() const {
    return _path;
}

const std::string& Request::getVersion() const {
    return _version;
}

const std::string& Request::getHeader(const std::string& key) const {
    static const std::string empty;
    std::map<std::string, std::string>::const_iterator it = _headers.find(key);
    return it != _headers.end() ? it->second : empty;
}

bool Request::hasHeader(const std::string& key) const {
    return _headers.find(key) != _headers.end();
}
