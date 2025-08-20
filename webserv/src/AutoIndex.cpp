#include "AutoIndex.hpp"
#include "Utils.hpp"
#include <dirent.h>

namespace AutoIndex {

std::string generate(const std::string &uriPath, const std::string &fsPath) {
	std::string html = "<!doctype html><html><body><h1>Index of " + uriPath + "</h1><ul>";
	DIR *d = opendir(fsPath.c_str());
	if (!d) return "<!doctype html><html><body><h1>Forbidden</h1></body></html>";
	struct dirent *e;
	while ((e = readdir(d))) {
		std::string name = e->d_name;
		if (name == ".") continue;
		std::string link = uriPath;
		if (!Utils::endsWith(link, "/")) link += "/";
		link += name;
		html += "<li><a href=\"" + link + "\">" + name + "</a></li>";
	}
	closedir(d);
	html += "</ul></body></html>";
	return html;
}

}
