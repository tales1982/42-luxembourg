/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:02:19 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/09 16:41:01 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

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

    std::cout << "\033[34m\n### TESTING COPY CONSTRUCTOR AND ASSIGNMENT ###\033[0m" << std::endl;
    FragTrap fragCopy(frag);       // Testando o construtor de cópia
    fragCopy.highFivesGuys();

    FragTrap fragAssigned("Temp");
    fragAssigned = frag;           // Testando o operador de atribuição
    fragAssigned.highFivesGuys();

    std::cout << "\033[34m\n### END OF TESTS ###\033[0m" << std::endl;
    return 0;
}
