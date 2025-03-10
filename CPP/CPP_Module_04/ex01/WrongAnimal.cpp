/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:19:25 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:09:36 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : type("WrongAnimal")
{
	std::cout << YELLOW << "Constructeur de WrongAnimal appelé !" << RESET << std::endl;
}

WrongAnimal::~WrongAnimal()
{
	std::cout << YELLOW << "Destructeur de WrongAnimal appelé !" << RESET << std::endl;
}

std::string WrongAnimal::getType() const
{
	return (type);
}

void WrongAnimal::makeSound() const
{
	std::cout << YELLOW << "WrongAnimal fait un son générique !" << RESET << std::endl;
}
