/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:32:10 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:11:04 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

AAnimal::AAnimal() : _type("AAnimal")
{
	std::cout << YELLOW << "Constructeur de AAnimal appelé !" << RESET << std::endl;
}

AAnimal::AAnimal(const AAnimal &other) : _type(other._type)
{
	std::cout << YELLOW << "Constructeur de copie de AAnimal appelé !" << RESET << std::endl;
}

AAnimal &AAnimal::operator=(const AAnimal &other)
{
	if (this != &other)
		_type = other._type;
	std::cout << YELLOW << "Opérateur d'affectation de AAnimal appelé !" << RESET << std::endl;
	return (*this);
}

AAnimal::~AAnimal()
{
	std::cout << YELLOW << "Destructeur de AAnimal appelé !" << RESET << std::endl;
}

void AAnimal::makeSound() const
{
	std::cout << YELLOW << "AAnimal fait un son générique !" << RESET << std::endl;
}

std::string AAnimal::getType() const
{
	return (_type);
}
