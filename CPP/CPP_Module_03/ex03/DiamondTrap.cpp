/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:57:27 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/09 17:30:21 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

// Construtor padrão
DiamondTrap::DiamondTrap() : ClapTrap("Default_clap_name"), FragTrap(), ScavTrap()
{
    _name = "Default";
    _hitPoints = 100;
    _energyPoints = 50;
    _attackDamage = 30;
    std::cout << "DiamondTrap default constructor called for " << _name << "." << std::endl;
}

// Construtor com parâmetro
DiamondTrap::DiamondTrap(const std::string &name)
    : ClapTrap(name + "_clap_name"), FragTrap(), ScavTrap()
{
    _name = name;
    _hitPoints = 100;
    _energyPoints = 50;
    _attackDamage = 30;
    std::cout << "DiamondTrap " << _name << " has been created!" << std::endl;
}

// Construtor de cópia
DiamondTrap::DiamondTrap(const DiamondTrap &copy) : ClapTrap(copy), FragTrap(copy), ScavTrap(copy)
{
    _name = copy._name;
    std::cout << "DiamondTrap copy constructor called for " << _name << "." << std::endl;
}

// Destrutor
DiamondTrap::~DiamondTrap()
{
    std::cout << "DiamondTrap " << _name << " has been destroyed!" << std::endl;
}

// Operador de atribuição
DiamondTrap &DiamondTrap::operator=(const DiamondTrap &src)
{
    ClapTrap::operator=(src);
    FragTrap::operator=(src);
    ScavTrap::operator=(src);
    _name = src._name;
    std::cout << "DiamondTrap assignation operator called for " << _name << "." << std::endl;
    return *this;
}

// whoAmI() Method
void DiamondTrap::whoAmI()
{
    std::cout << "DiamondTrap name: " << _name
              << ", ClapTrap name: " << ClapTrap::_name << std::endl;
}
