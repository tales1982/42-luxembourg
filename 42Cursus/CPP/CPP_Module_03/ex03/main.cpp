/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:02:19 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/09 17:36:31 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"

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

    std::cout << "\033[34m\n### TESTING FRAGTRAP ###\033[0m" << std::endl;
    FragTrap frag("Fraggy");
    frag.attack("enemy");          // Testando ataque herdado
    frag.takeDamage(30);           // Testando dano herdado
    frag.beRepaired(20);           // Testando reparo herdado
    frag.highFivesGuys();          // Testando método exclusivo

    std::cout << "\033[34m\n### TESTING DIAMONDTRAP ###\033[0m" << std::endl;
    DiamondTrap diamond("Diamondy");
    diamond.attack("enemy");       // Testando o ataque (ScavTrap)
    diamond.takeDamage(40);        // Testando dano herdado
    diamond.beRepaired(25);        // Testando reparo herdado
    diamond.whoAmI();              // Testando método exclusivo

    std::cout << "\033[34m\n### TESTING COPY CONSTRUCTOR AND ASSIGNMENT ###\033[0m" << std::endl;
    DiamondTrap diamondCopy(diamond); // Testando o construtor de cópia
    diamondCopy.whoAmI();

    DiamondTrap diamondAssigned("Temp");
    diamondAssigned = diamond;     // Testando o operador de atribuição
    diamondAssigned.whoAmI();

    std::cout << "\033[34m\n### END OF TESTS ###\033[0m" << std::endl;
    return 0;
}
