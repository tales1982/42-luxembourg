/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:26:33 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/09 16:21:15 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "ClapTrap.hpp"

//construtor com parametro
ClapTrap::ClapTrap(std::string name) : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
    std::cout << "ClapTrap Constructor for the name " << _name << " called" << std::endl;
}


//construtor sem parametro e inicializo as variaveis.
ClapTrap::ClapTrap() : _name("default"), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
    std::cout << "ClapTrap " << _name << " constructor called." << std::endl;

}
//construtor que fais copia
ClapTrap::ClapTrap(const ClapTrap &copy) : _name(copy._name), _hitPoints(copy._hitPoints), _energyPoints(copy._energyPoints), _attackDamage(copy._attackDamage)
{
    std::cout << "ClapTrap Copy Constructor called" << std::endl;
}

// Overloaded Operators
ClapTrap &ClapTrap::operator=(const ClapTrap &src)
{
	std::cout << "ClapTrap Assignation operator called" << std::endl;
	this->_name = src._name;
	this->_hitPoints = src._hitPoints;
	this->_energyPoints = src._energyPoints;
	this->_attackDamage = src._attackDamage;
	return *this;
}



//construtor q destroi
ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap " << _name << " destructor called." << std::endl;
}



void ClapTrap::attack(const std::string &target)
{
    if(this->_energyPoints > 0 && this->_hitPoints > 0)
   	{
		std::cout << "ClapTrap " << this->_name << " attacks " << target << ", causing " << this->_attackDamage << " points of damage!" << std::endl;
		this->_energyPoints--;
	}
	else if (this->_energyPoints == 0)
		std::cout << "\033[31mClapTrap " << this->_name << " is not able to attack " << target << ", because he has no energy points left.\033[0m" << std::endl;
	else
		std::cout << "\033[31mClapTrap " << this->_name << " is not able to attack " << target << ", because he has not enough hit points.\033[0m" << std::endl;

}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (this->_hitPoints > amount)
		this->_hitPoints -= amount;
	else if (this->_hitPoints > 0)
		this->_hitPoints = 0;
	else
	{
		std::cout << "\033[33mClapTrap " << this->_name << " is already dead, stop beating it.\033[0m" << std::endl;
		return ;
	}
	std::cout << "ClapTrap " << this->_name << " was attacked and lost " << amount << " hit points, he now has " << this->_hitPoints << " hit points." << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (this->_energyPoints > 0 && this->_hitPoints > 0 && this->_hitPoints + amount <= 10)
	{
		this->_hitPoints += amount;
		std::cout << "ClapTrap " << this->_name << " repaired itself and gained " << amount << " of hit points, he now has " << this->_hitPoints << "hit points." << std::endl;
		this->_energyPoints--;
	}
	else if (this->_energyPoints == 0)
		std::cout << "\033[31mClapTrap " << this->_name << " is not able to repair itself, because he doesn't have enough energy points.\033[0m" << std::endl;
	else if (this->_hitPoints == 0)
		std::cout << "\033[31mClapTrap " << this->_name << " is not able to repair itself, because he doesn't have enough hit points.\033[0m" << std::endl;
	else
		std::cout << "\033[33mClapTrap " << this->_name << " can't be repaired to have more than 10 hit points.\033[0m" << std::endl;
}
