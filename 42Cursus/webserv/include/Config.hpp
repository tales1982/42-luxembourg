/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:15:40 by tales             #+#    #+#             */
/*   Updated: 2025/09/01 09:15:41 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <vector>
#include <map>
#include <cstddef>

struct LocationConfig {
	std::string path;
	std::vector<std::string> methods;
	std::string root;
	bool autoindex;
	std::string index;
	bool upload_on;
	std::string upload_store;
	std::string redirect;
	std::string cgi_ext;
	std::string cgi_executor;
	LocationConfig();
};

struct ServerConfig {
	std::string host;
	int port;
	std::vector<std::string> server_names;
	std::string root;
	size_t client_max_body_size;
	std::map<int, std::string> error_pages;
	std::vector<LocationConfig> locations;
	bool is_default;
	ServerConfig();
};

struct GlobalConfig {
	std::vector<ServerConfig> servers;
};

class ConfigParser {
public:
	GlobalConfig parseFile(const std::string &path);
};

#endif
