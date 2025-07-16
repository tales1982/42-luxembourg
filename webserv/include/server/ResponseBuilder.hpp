/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseBuilder.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:05:40 by tales             #+#    #+#             */
/*   Updated: 2025/07/16 11:26:17 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// include/server/ResponseBuilder.hpp
#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>
std::string read_file(const std::string& path);
std::string get_mime_type(const std::string& path);
std::string replace_placeholder(std::string source, const std::string& placeholder, const std::string& value);
std::string generate_autoindex(const std::string& dirPath, const std::string& urlPath);
std::string generate_all_uploads_page();