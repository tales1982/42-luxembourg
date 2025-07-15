/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:48:58 by tlima-de          #+#    #+#             */
/*   Updated: 2025/07/15 10:49:02 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/Server.hpp"
#include "../include/ConfigParser.hpp"

int main(int ac, char **av) {
    std::string configPath = (ac == 2) ? av[1] : "default.conf";
    ServerConfig conf = parse_config(configPath);

    std::cout << "Config Loaded:\n";
    std::cout << "Port: " << conf.port << "\n";
    std::cout << "Host: " << conf.host << "\n";
    std::cout << "Root: " << conf.root << "\n";

    return ft_server(conf); // próximo passo: adaptar ft_server para receber isso
}
