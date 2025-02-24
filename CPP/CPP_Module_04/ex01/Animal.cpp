/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:32:10 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:36:33 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() : _type("Animal")
{
    std::cout << "Construtor de Animal chamado!" << std::endl;
}

Animal::Animal(const Animal& other) : _type(other._type)
{
    std::cout << "Construtor de cópia de Animal chamado!" << std::endl;
}

Animal& Animal::operator=(const Animal& other)
{
    if (this != &other) 
        _type = other._type;
    std::cout << "Operador de atribuição de Animal chamado!" << std::endl;
    return *this;
}

Animal::~Animal()
{
    std::cout << "Destrutor de Animal chamado!" << std::endl;
}

void Animal::makeSound() const
{
    std::cout << "Animal faz um som genérico!" << std::endl;
}

std::string Animal::getType() const
{
    return _type;
}
