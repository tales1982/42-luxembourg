/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:40:47 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 15:50:28 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

// Constructeur par défaut
WrongAnimal::WrongAnimal() : type("WrongAnimal")
{
    std::cout << CYAN << "Constructeur de WrongAnimal appelé !" << RESET << std::endl;
}

// Destructeur
WrongAnimal::~WrongAnimal()
{
    std::cout << CYAN <<  "Destructeur de WrongAnimal appelé !" << RESET << std::endl;
}

// Retourne le type de l'animal
std::string WrongAnimal::getType() const
{
    return type;
}

// Émet un son générique pour la classe WrongAnimal
void WrongAnimal::makeSound() const
{
    std::cout << CYAN << "WrongAnimal fait un son générique !" << RESET << std::endl;
}
