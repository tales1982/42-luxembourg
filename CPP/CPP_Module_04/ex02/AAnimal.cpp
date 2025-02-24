/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:32:10 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:37:56 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

AAnimal::AAnimal() : _type("AAnimal")
{
    std::cout << "Construtor de AAnimal chamado!" << std::endl;
}

AAnimal::AAnimal(const AAnimal& other) : _type(other._type)
{
    std::cout << "Construtor de cópia de AAnimal chamado!" << std::endl;
}

AAnimal& AAnimal::operator=(const AAnimal& other)
{
    if (this != &other) 
        _type = other._type;
    std::cout << "Operador de atribuição de AAnimal chamado!" << std::endl;
    return *this;
}

AAnimal::~AAnimal()
{
    std::cout << "Destrutor de AAnimal chamado!" << std::endl;
}

void AAnimal::makeSound() const
{
    std::cout << "Animal faz um som genérico!" << std::endl;
}

std::string AAnimal::getType() const
{
    return _type;
}
