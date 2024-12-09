/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:26:04 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/09 16:38:54 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

// Construtor padrão
FragTrap::FragTrap() : ClapTrap("Default FragTrap") {
    _hitPoints = 100;
    _energyPoints = 100;
    _attackDamage = 30;
    std::cout << "FragTrap default constructor called for " << _name << "." << std::endl;
}

// Construtor por cópia
FragTrap::FragTrap(const FragTrap &copy) : ClapTrap(copy) {
    std::cout << "FragTrap copy constructor called for " << _name << "." << std::endl;
}

// Construtor com parâmetro
FragTrap::FragTrap(const std::string &name) : ClapTrap(name) {
    _hitPoints = 100;
    _energyPoints = 100;
    _attackDamage = 30;
    std::cout << "FragTrap " << _name << " has been created!" << std::endl;
}

// Destrutor
FragTrap::~FragTrap() {
    std::cout << "FragTrap " << _name << " has been destroyed!" << std::endl;
}

// Operador de atribuição
FragTrap &FragTrap::operator=(const FragTrap &src) {
    ClapTrap::operator=(src);
    std::cout << "FragTrap assignation operator called for " << _name << "." << std::endl;
    return *this;
}

// Método público
void FragTrap::highFivesGuys(void) {
    std::cout << "FragTrap " << _name << " requests a high five!" << std::endl;
}
