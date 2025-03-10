/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:10:32 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:04:25 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
{
	type = YELLOW "Cat" RESET;
	std::cout << YELLOW << "Constructeur de Cat appelé !" << RESET << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other)
{
	std::cout << YELLOW << "Constructeur de copie de Cat appelé !" << RESET << std::endl;
}

Cat &Cat::operator=(const Cat &other)
{
	if (this != &other)
		Animal::operator=(other);
	std::cout << YELLOW << "Opérateur d'affectation de Cat appelé !" << RESET << std::endl;
	return (*this);
}

Cat::~Cat()
{
	std::cout << YELLOW << "Destructeur de Cat appelé !" << RESET << std::endl;
}

void Cat::makeSound() const
{
	std::cout << YELLOW << "Cat fait : Meowww ! Meowww !" << RESET << std::endl;
}
