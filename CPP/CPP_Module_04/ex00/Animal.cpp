/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:19:13 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/10 20:10:20 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

// Construtor padrão
Animal::Animal() : _type("Default")
{
    std::cout << BLUE << "Default constructor initialized. Class Animal." << RESET << std::endl;
}

// Construtor com parâmetro
Animal::Animal(std::string name) : _type(name)
{
    std::cout << BLUE << "Parameter constructor initialized. Class Animal." << RESET << std::endl;
}

// Construtor de cópia
Animal::Animal(const Animal &copy) : _type(copy._type)
{
    std::cout << BLUE << "Copy constructor initialized. Class Animal." << RESET << std::endl;
}

// Operador de atribuição
Animal &Animal::operator=(const Animal &src)
{
    if (this != &src) { // Verifica auto-atribuição
        this->_type = src._type;
    }
    std::cout << BLUE << "Assignment operator called. Class Animal." << RESET << std::endl;
    return *this;
}

// Destrutor
Animal::~Animal()
{
    std::cout << RED << "Destructor called. Class Animal." << RESET << std::endl;
}

// Método adicional: getType
std::string Animal::getType() const
{
    return _type;
}

// Método adicional: makeSound
void Animal::makeSound() const
{
    std::cout << BLUE << "Default animal sound. Class Animal." << RESET << std::endl;
}
