/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:16:33 by tales             #+#    #+#             */
/*   Updated: 2025/07/16 09:16:52 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// src/main.cpp
#include "../include/server/Server.hpp"
#include "../include/parser/ConfigParser.hpp"
#include <iostream>

int main(int ac, char **av) {
    std::string configPath = (ac == 2) ? av[1] : "default.conf";
    ServerConfig conf = parse_config(configPath);

    std::cout << "Config Loaded:\n";
    std::cout << "Port: " << conf.port << "\n";
    std::cout << "Host: " << conf.host << "\n";
    std::cout << "Root: " << conf.root << "\n";

    return ft_server(conf);
}