/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:48:14 by tlima-de          #+#    #+#             */
/*   Updated: 2025/07/15 10:48:19 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "Config.hpp"
#include <iostream>
#include <ctime>
#include <cstring>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <algorithm>
#include <fcntl.h>
#include <cerrno>
#include <arpa/inet.h> // necessário para inet_addr

int ft_server(const ServerConfig& config);
