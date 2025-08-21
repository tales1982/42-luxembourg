#include "Utils.hpp"
#include <algorithm>
#include <sstream>
#include <fstream>
#include <sys/stat.h>
#include <dirent.h>
#include <ctime>

namespace Utils {

std::string trim(const std::string &s) {
	size_t b = 0; while (b < s.size() && (s[b] == ' ' || s[b] == '\t' || s[b] == '\r' || s[b] == '\n')) b++;
	size_t e = s.size(); while (e>b && (s[e-1]==' '||s[e-1]=='\t'||s[e-1]=='\r'||s[e-1]=='\n')) e--;
	return s.substr(b, e-b);
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> v; std::string cur; std::istringstream is(s);
	while (std::getline(is, cur, delim)) v.push_back(cur);
	return v;
}

std::string toLower(const std::string &s) {
	std::string r = s; for (size_t i=0;i<r.size();++i) r[i] = (char)std::tolower(r[i]); return r;
}

static int hexval(char c) {
	if (c>='0'&&c<='9') return c-'0';
	if (c>='a'&&c<='f') return 10 + c-'a';
	if (c>='A'&&c<='F') return 10 + c-'A';
	return -1;
}

std::string urlDecode(const std::string &s) {
	std::string o; o.reserve(s.size());
	for (size_t i=0;i<s.size();++i) {
		if (s[i]=='%' && i+2<s.size()) {
			int h1 = hexval(s[i+1]); int h2 = hexval(s[i+2]);
			if (h1>=0 && h2>=0) { o.push_back((char)((h1<<4)|h2)); i+=2; }
			else o.push_back(s[i]);
		} else if (s[i]=='+') o.push_back(' ');
		else o.push_back(s[i]);
	}
	return o;
}

std::string getTimeRfc1123() {
	char buf[128]; std::time_t t = std::time(0); std::tm *gmt = std::gmtime(&t);
	std::strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", gmt);
	return std::string(buf);
}

std::string guessMime(const std::string &path) {
	if (endsWith(path, ".html") || endsWith(path, ".htm")) return "text/html";
	if (endsWith(path, ".css")) return "text/css";
	if (endsWith(path, ".js")) return "application/javascript";
	if (endsWith(path, ".png")) return "image/png";
	if (endsWith(path, ".jpg") || endsWith(path, ".jpeg")) return "image/jpeg";
	if (endsWith(path, ".gif")) return "image/gif";
	if (endsWith(path, ".txt")) return "text/plain";
	return "application/octet-stream";
}

bool startsWith(const std::string &s, const std::string &prefix) {
	return s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0;
}
bool endsWith(const std::string &s, const std::string &suffix) {
	return s.size() >= suffix.size() && s.compare(s.size()-suffix.size(), suffix.size(), suffix) == 0;
}

std::string joinPath(const std::string &a, const std::string &b) {
	if (a.empty()) return b;
	if (a[a.size()-1] == '/') return a + b;
	return a + "/" + b;
}

std::string safePathJoin(const std::string &root, const std::string &rel) {
	std::string p = joinPath(root, rel);
	if (p.find("..") != std::string::npos) return root;
	return p;
}

std::string readFile(const std::string &path) {
	std::ifstream f(path.c_str(), std::ios::in | std::ios::binary);
	if (!f) return "";
	std::ostringstream ss; ss << f.rdbuf();
	return ss.str();
}

bool fileExists(const std::string &path) {
	struct stat st; return stat(path.c_str(), &st) == 0;
}

bool isDir(const std::string &path) {
	struct stat st; if (stat(path.c_str(), &st) != 0) return false; return S_ISDIR(st.st_mode);
}
size_t fileSize(const std::string &path) {
	struct stat st; if (stat(path.c_str(), &st) != 0) return 0; return (size_t)st.st_size;
}

std::string itoa(int v) { std::ostringstream ss; ss<<v; return ss.str(); }
std::string utoa(size_t v) { std::ostringstream ss; ss<<v; return ss.str(); }

}

std::string Utils::toUpper(const std::string &s) {
    std::string out = s;
    for (size_t i = 0; i < out.size(); ++i) {
        out[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(out[i])));
    }
    return out;
}
