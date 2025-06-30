#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <map>

class Request {
public:
    Request(const std::string& rawRequest);
    const std::string& getMethod() const;
    const std::string& getPath() const;
    const std::string& getVersion() const;
    const std::string& getHeader(const std::string& key) const;
    bool hasHeader(const std::string& key) const;

private:
    std::string _method;
    std::string _path;
    std::string _version;
    std::map<std::string, std::string> _headers;
    void parse(const std::string& raw);
};

#endif
