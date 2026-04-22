/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:19:05 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:08:48 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : _brain(new Brain())
{
	_type = "Cat";
	std::cout << RED << "Construtor de Cat chamado!" << RESET << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other), _brain(new Brain(*other._brain))
{
	std::cout << RED << "Construtor de cópia de Cat chamado!" << RESET << std::endl;
}

Cat &Cat::operator=(const Cat &other)
{
	if (this != &other)
	{
		Animal::operator=(other);
		*_brain = *other._brain;
	}
	std::cout << RED << "Operador de atribuição de Cat chamado!" << RESET << std::endl;
	return (*this);
}

Cat::~Cat()
{
	delete	_brain;

	std::cout << RED << "Destrutor de Cat chamado!" << RESET << std::endl;
}

void Cat::makeSound() const
{
	std::cout << RED << "Cat faz: Meowww! Meowww!" << RESET << std::endl;
}

Brain *Cat::getBrain() const
{
	return (_brain);
}