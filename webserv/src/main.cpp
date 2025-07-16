/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:48:58 by tlima-de          #+#    #+#             */
/*   Updated: 2025/07/16 11:09:12 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/server/Server.hpp"
#include "../include/parser/ConfigParser.hpp"

int main(int ac, char **av) {
    std::string configPath = (ac == 2) ? av[1] : "default.conf";
    ServerConfig conf = parse_config(configPath);

    std::cout << "Config Loaded:\n";
    std::cout << "Port: " << conf.port << "\n";
    std::cout << "Host: " << conf.host << "\n";
    std::cout << "Root: " << conf.root << "\n";

    return ft_server(conf); // próximo passo: adaptar ft_server para receber isso
}
