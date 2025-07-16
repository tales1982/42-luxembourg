/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:00:14 by tales             #+#    #+#             */
/*   Updated: 2025/07/16 16:00:15 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#pragma once

#include "../config/Config.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

ServerConfig parse_config(const std::string& path);
