/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:48:14 by tlima-de          #+#    #+#             */
/*   Updated: 2025/07/16 11:11:27 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "../config/Config.hpp"
#include <iostream>
#include <map>
#include <ctime>
#include <cstring>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <algorithm>
#include <fcntl.h>
#include <cerrno>
#include <arpa/inet.h> 
#include <cctype>    
#include <strings.h> 

int ft_server(const ServerConfig& config);