/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:02:42 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/09 13:14:11 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

// Construtor padrão
ScavTrap::ScavTrap() : ClapTrap("default") {
    _hitPoints = 100;
    _energyPoints = 50;
    _attackDamage = 20;
    std::cout << "ScavTrap default constructor called for " << _name << "." << std::endl;
}

// Construtor parametrizado
ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name) {
    _hitPoints = 100;
    _energyPoints = 50;
    _attackDamage = 20;
    std::cout << "ScavTrap constructor called for " << _name << "." << std::endl;
}

// Construtor de cópia
ScavTrap::ScavTrap(const ScavTrap &copy) : ClapTrap(copy) {
    std::cout << "ScavTrap copy constructor called for " << _name << "." << std::endl;
}

// Destrutor
ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap destructor called for " << _name << "." << std::endl;
}

// Operador de atribuição
ScavTrap &ScavTrap::operator=(const ScavTrap &src) {
    ClapTrap::operator=(src);
    std::cout << "ScavTrap assignation operator called for " << _name << "." << std::endl;
    return *this;
}

// Método attack redefinido
void ScavTrap::attack(const std::string &target) {
    if (_energyPoints > 0 && _hitPoints > 0) {
        std::cout << "ScavTrap " << _name << " ferociously attacks " << target
                  << ", causing " << _attackDamage << " points of damage!" << std::endl;
        _energyPoints--;
    } else {
        std::cout << "ScavTrap " << _name << " cannot attack due to insufficient energy or health." << std::endl;
    }
}

// Método exclusivo guardGate
void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << _name << " is now in Gate keeper mode!" << std::endl;
}
