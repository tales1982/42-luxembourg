/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:11:58 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:05:53 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
{
	type = BLUE "Dog" RESET;
	std::cout << BLUE << "Constructeur de Dog appelé !" << RESET << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other)
{
	std::cout << BLUE << "Constructeur de copie de Dog appelé !" << RESET << std::endl;
}

Dog &Dog::operator=(const Dog &other)
{
	if (this != &other)
		Animal::operator=(other);
	std::cout << BLUE << "Opérateur d'affectation de Dog appelé !" << RESET << std::endl;
	return (*this);
}

Dog::~Dog()
{
	std::cout << BLUE << "Destructeur de Dog appelé !" << RESET << std::endl;
}

void Dog::makeSound() const
{
	std::cout << BLUE << "Dog fait : Woof ! Woof !" << RESET << std::endl;
}
