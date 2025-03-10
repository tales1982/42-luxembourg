/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:40:19 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:13:54 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : _brain(new Brain())
{
	_type = "Cat";
	std::cout << RED << "Constructeur de Cat appelé !" << RESET << std::endl;
}

Cat::Cat(const Cat &other) : AAnimal(other), _brain(new Brain(*other._brain))
{
	std::cout << RED << "Constructeur de copie de Cat appelé !" << RESET << std::endl;
}

Cat &Cat::operator=(const Cat &other)
{
	if (this != &other)
	{
		AAnimal::operator=(other);
		*_brain = *other._brain; // Copie profonde
	}
	std::cout << RED << "Opérateur d'affectation de Cat appelé !" << RESET << std::endl;
	return (*this);
}

Cat::~Cat()
{
	delete	_brain;

	std::cout << RED << "Destructeur de Cat appelé !" << RESET << std::endl;
}

void Cat::makeSound() const
{
	std::cout << RED << "Cat fait : Meowww ! Meowww !" << RESET << std::endl;
}

Brain *Cat::getBrain() const
{
	return (_brain);
}
