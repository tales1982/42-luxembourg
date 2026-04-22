/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:02:19 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/09 16:45:03 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ClapTrap.hpp"
#include"ScavTrap.hpp"

int main() {
    std::cout << "\033[34m### TESTING CLAPTRAP ###\033[0m" << std::endl;
    ClapTrap clap("Clappy");
    clap.attack("enemy");
    clap.takeDamage(5);
    clap.beRepaired(3);

    std::cout << "\033[34m\n### TESTING SCAVTRAP ###\033[0m" << std::endl;
    ScavTrap scav("Scavvy");
    scav.attack("enemy");
    scav.takeDamage(20);
    scav.beRepaired(10);
    scav.guardGate();
     std::cout << "\033[34m\n### END OF TESTS ###\033[0m" << std::endl;
    return 0;
}
