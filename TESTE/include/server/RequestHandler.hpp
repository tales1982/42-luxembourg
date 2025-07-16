/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:05:18 by tales             #+#    #+#             */
/*   Updated: 2025/07/16 09:05:20 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// include/server/RequestHandler.hpp
#pragma once
#include "../config/Config.hpp"
const LocationConfig* match_location(const ServerConfig& config, const std::string& path);
std::string get_upload_dir_by_extension(const std::string& filename);