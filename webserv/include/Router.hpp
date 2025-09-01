/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:16:10 by tales             #+#    #+#             */
/*   Updated: 2025/09/01 09:16:11 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTER_HPP
#define ROUTER_HPP

#include "Config.hpp"
#include "Http.hpp"
#include <string>

struct RouteMatch {
	const ServerConfig *server;
	const LocationConfig *loc;
	std::string fsRoot;
	std::string relPath;
};

class Router {
public:
	Router(const GlobalConfig &gc);
	RouteMatch match(const HttpRequest &req) const;
	const GlobalConfig &config() const { return _conf; }
private:
	const GlobalConfig &_conf;
	const ServerConfig* pickServer(const HttpRequest &req) const;
	const LocationConfig* pickLocation(const ServerConfig *srv, const std::string &uri) const;
};

#endif
