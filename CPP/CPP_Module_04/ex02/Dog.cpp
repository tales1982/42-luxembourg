/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:40:29 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:14:16 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : _brain(new Brain())
{
	_type = "Dog";
	std::cout << GREEN << "Constructeur de Dog appelé !" << RESET << std::endl;
}

Dog::Dog(const Dog &other) : AAnimal(other), _brain(new Brain(*other._brain))
{
	std::cout << GREEN << "Constructeur de copie de Dog appelé !" << RESET << std::endl;
}

Dog &Dog::operator=(const Dog &other)
{
	if (this != &other)
	{
		AAnimal::operator=(other);
		*_brain = *other._brain;
	}
	std::cout << GREEN << "Opérateur d'affectation de Dog appelé !" << RESET << std::endl;
	return (*this);
}

Dog::~Dog()
{
	delete	_brain;

	std::cout << GREEN << "Destructeur de Dog appelé !" << RESET << std::endl;
}

void Dog::makeSound() const
{
	std::cout << GREEN << "Dog fait : Woof ! Woof !" << RESET << std::endl;
}

Brain *Dog::getBrain() const
{
	return (_brain);
}
