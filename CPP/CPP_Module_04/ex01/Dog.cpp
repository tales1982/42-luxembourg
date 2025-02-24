/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:28:49 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:37:00 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : _brain(new Brain())
{
    _type = "Dog";
    std::cout << "Construtor de Dog chamado!" << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other), _brain(new Brain(*other._brain))
{
    std::cout << "Construtor de cópia de Dog chamado!" << std::endl;
}

Dog& Dog::operator=(const Dog& other)
{
    if (this != &other)
	{	
        Animal::operator=(other);
		*_brain = *other._brain;  // Copia profunda
	}
    std::cout << "Operador de atribuição de Dog chamado!" << std::endl;
    return *this;
}

Dog::~Dog()
{
	delete _brain;
    std::cout << "Destrutor de Dog chamado!" << std::endl;
}

void Dog::makeSound() const
{
    std::cout << "Dog faz: Woof! Woof!" << std::endl;
}

Brain* Dog::getBrain() const
{
    return _brain;
}
