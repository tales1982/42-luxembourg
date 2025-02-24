/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:21:43 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:36:50 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : _brain(new Brain())
{
    _type = "Cat";
    std::cout << "Construtor de Cat chamado!" << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other), _brain(new Brain(*other._brain))
{
    std::cout << "Construtor de cópia de Cat chamado!" << std::endl;
}

Cat& Cat::operator=(const Cat& other)
{
    if (this != &other)
	{	
        Animal::operator=(other);
		*_brain = *other._brain; // Copia profunda
	}
    std::cout << "Operador de atribuição de Cat chamado!" << std::endl;
    return *this;
}

Cat::~Cat()
{
	delete _brain;
    std::cout << "Destrutor de Cat chamado!" << std::endl;
}

void Cat::makeSound() const
{
    std::cout << "Cat faz: Meowww! Meowww!" << std::endl;
}

Brain* Cat::getBrain() const
{
    return _brain;
}
