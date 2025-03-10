/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:04:57 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:04:11 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() : type("Animal")
{
	std::cout << GREEN << "Constructeur de Animal appelé !" << RESET << std::endl;
}

Animal::Animal(const Animal &other) : type(other.type)
{
	std::cout << GREEN << "Constructeur de copie de Animal appelé !" << RESET << std::endl;
}

Animal &Animal::operator=(const Animal &other)
{
	if (this != &other)
		type = other.type;
	std::cout << GREEN << "Opérateur d'affectation de Animal appelé !" << RESET << std::endl;
	return (*this);
}

Animal::~Animal()
{
	std::cout << GREEN << "Destructeur de Animal appelé !" << RESET << std::endl;
}

void Animal::makeSound() const
{
	std::cout << GREEN << "Animal fait un son générique !" << RESET << std::endl;
}

std::string Animal::getType() const
{
	return (type);
}
