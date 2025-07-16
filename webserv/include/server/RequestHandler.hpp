/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:05:18 by tales             #+#    #+#             */
/*   Updated: 2025/07/16 11:32:14 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// include/server/RequestHandler.hpp
#pragma once
#include "../config/Config.hpp"

#include <fstream>
#include <sstream>
#include <arpa/inet.h> // inet_addr
#include <sys/stat.h>  // mkdir
#include <cstring>     // memset
#include <dirent.h>    // para ler diretórios

std::string get_requested_path(const std::string &request);
const LocationConfig* match_location(const ServerConfig& config, const std::string& path);
std::string get_upload_dir_by_extension(const std::string& filename);