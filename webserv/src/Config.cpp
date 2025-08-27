#include "Config.hpp"
#include "Utils.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <iostream>

LocationConfig::LocationConfig() : autoindex(false), upload_on(false) {}
ServerConfig::ServerConfig() : port(8080), client_max_body_size(1024 * 1024), is_default(false) {}

GlobalConfig ConfigParser::parseFile(const std::string &path)
{
	std::ifstream f(path.c_str());
	if (!f)
		throw std::runtime_error("Could not open config: " + path);
	std::stringstream buf;
	buf << f.rdbuf();
	std::string s = buf.str();

	// remove comments
	std::string t;
	t.reserve(s.size());
	for (size_t i = 0; i < s.size(); ++i)
	{
		if (s[i] == '#')
		{
			while (i < s.size() && s[i] != '\n')
				++i;
		}
		else
			t.push_back(s[i]);
	}
	s = t;

	GlobalConfig gc;
	std::istringstream is(s);
	std::string tok;
	while (is >> tok)
	{
		if (tok == "server")
		{
			std::string br;
			is >> br; // "{"
			ServerConfig srv;
			if (gc.servers.empty())
				srv.is_default = true;
			while (is >> tok)
			{
				if (tok == "}")
					break;
				if (tok == "listen")
				{
					std::string hp;
					is >> hp;
					if (hp[hp.size() - 1] == ';')
						hp.erase(hp.size() - 1);
					size_t colon = hp.find(':');
					srv.host = (colon == std::string::npos) ? "0.0.0.0" : hp.substr(0, colon);
					srv.port = std::atoi((colon == std::string::npos) ? hp.c_str() : hp.substr(colon + 1).c_str());
				}
				else if (tok == "server_name")
				{
					std::string name;
					while (is >> name)
					{
						if (name[name.size() - 1] == ';')
						{
							name.erase(name.size() - 1);
							srv.server_names.push_back(name);
							break;
						}
						srv.server_names.push_back(name);
					}
				}
				else if (tok == "root")
				{
					std::string rp;
					is >> rp;
					if (rp[rp.size() - 1] == ';')
						rp.erase(rp.size() - 1);
					srv.root = rp;
				}
				else if (tok == "client_max_body_size")
				{
					std::string v;
					is >> v;
					if (v[v.size() - 1] == ';')
						v.erase(v.size() - 1);
					size_t mult = 1;
					if (!v.empty())
					{
						char last = v[v.size() - 1];
						if (last == 'm' || last == 'M')
						{
							mult = 1024 * 1024;
							v.erase(v.size() - 1);
						}
						else if (last == 'k' || last == 'K')
						{
							mult = 1024;
							v.erase(v.size() - 1);
						}
					}
					srv.client_max_body_size = std::atoi(v.c_str()) * mult;
				}
				else if (tok == "error_page")
				{
					int code;
					is >> code;
					std::string p;
					is >> p;
					if (p[p.size() - 1] == ';')
						p.erase(p.size() - 1);
					srv.error_pages[code] = p;
				}
				else if (tok == "location")
				{
					LocationConfig loc;
					is >> loc.path;
					std::string br2;
					is >> br2; // "{"
					while (is >> tok)
					{
						if (tok == "}")
							break;
						if (tok == "methods")
						{
							std::string m;
							while (is >> m)
							{
								bool end = (!m.empty() && m[m.size() - 1] == ';');
								if (end)
									m.erase(m.size() - 1);
								for (size_t i = 0; i < m.size(); ++i)
									m[i] = toupper(m[i]); // <- força UPPER
								loc.methods.push_back(m);
								if (end)
									break;
							}
						}
						else if (tok == "root")
						{
							std::string rp;
							is >> rp;
							if (rp[rp.size() - 1] == ';')
								rp.erase(rp.size() - 1);
							loc.root = rp;
						}
						else if (tok == "autoindex")
						{
							std::string on;
							is >> on;
							if (on[on.size() - 1] == ';')
								on.erase(on.size() - 1);
							loc.autoindex = (on == "on");
						}
						else if (tok == "index")
						{
							std::string idx;
							is >> idx;
							if (idx[idx.size() - 1] == ';')
								idx.erase(idx.size() - 1);
							loc.index = idx;
						}
						else if (tok == "upload")
						{
							std::string on;
							is >> on;
							if (on[on.size() - 1] == ';')
								on.erase(on.size() - 1);
							loc.upload_on = (on == "on");
						}
						else if (tok == "upload_store")
						{
							std::string us;
							is >> us;
							if (us[us.size() - 1] == ';')
								us.erase(us.size() - 1);
							loc.upload_store = us;
						}
						else if (tok == "return")
						{
							std::string code;
							is >> code;
							std::string target;
							is >> target;
							if (target[target.size() - 1] == ';')
								target.erase(target.size() - 1);
							loc.redirect = code + " " + target;
						}
						else if (tok == "cgi_ext")
						{
							std::string ext;
							is >> ext;
							if (ext[ext.size() - 1] == ';')
								ext.erase(ext.size() - 1);
							loc.cgi_ext = ext;
						}
						else if (tok == "cgi_executor")
						{
							std::string ex;
							is >> ex;
							if (ex[ex.size() - 1] == ';')
								ex.erase(ex.size() - 1);
							loc.cgi_executor = ex;
						}
					}
					srv.locations.push_back(loc);
				}
			}
			if (srv.root.empty())
				srv.root = "./www";

// >>> COLE ESTE BLOCO AQUI <<<
// DEBUG: inspecionar locations carregadas
#include <iostream> // no topo do arquivo

			// ...dentro de parseFile, logo antes de gc.servers.push_back(srv);
			std::cerr << "[CONF] server root=" << srv.root
					  << " listen=" << srv.host << ":" << srv.port << "\n";
			for (size_t i = 0; i < srv.locations.size(); ++i)
			{
				const LocationConfig &L = srv.locations[i];
				std::cerr << "  - loc.path=" << L.path << " methods=";
				for (size_t j = 0; j < L.methods.size(); ++j)
					std::cerr << L.methods[j] << " ";
				std::cerr << " autoindex=" << (L.autoindex ? "on" : "off")
						  << " upload=" << (L.upload_on ? "on" : "off")
						  << " upload_store=" << (L.upload_store.empty() ? "(empty)" : L.upload_store)
						  << " redirect=\"" << L.redirect << "\"\n";
			}

			// <<< FIM DO BLOCO DE DEBUG >>>

			std::cerr << "[CONF] server root=" << srv.root
					  << " listen=" << srv.host << ":" << srv.port << "\n";
			for (size_t i = 0; i < srv.locations.size(); ++i)
			{
				const LocationConfig &L = srv.locations[i];
				std::cerr << "  - loc.path=" << L.path << " methods=";
				for (size_t j = 0; j < L.methods.size(); ++j)
					std::cerr << L.methods[j] << " ";
				std::cerr << " autoindex=" << (L.autoindex ? "on" : "off")
						  << " upload=" << (L.upload_on ? "on" : "off")
						  << " upload_store=" << (L.upload_store.empty() ? "(empty)" : L.upload_store)
						  << " redirect=\"" << L.redirect << "\"\n";
			}
			gc.servers.push_back(srv);
		}
	}
	return gc;
}
