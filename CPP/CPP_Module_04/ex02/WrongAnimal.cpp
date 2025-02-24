/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:29:34 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:38:40 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

// Construtor padrão
WrongAnimal::WrongAnimal() : type("WrongAnimal")
{
    std::cout << "Construtor de WrongAnimal chamado!" << std::endl;
}

// Destrutor
WrongAnimal::~WrongAnimal()
{
    std::cout << "Destrutor de WrongAnimal chamado!" << std::endl;
}

// Retorna o tipo do animal
std::string WrongAnimal::getType() const
{
    return type;
}

// Emite som genérico para a classe WrongAnimal
void WrongAnimal::makeSound() const
{
    std::cout << "WrongAnimal faz um som genérico!" << std::endl;
}
