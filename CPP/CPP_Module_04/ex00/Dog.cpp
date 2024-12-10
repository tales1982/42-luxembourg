/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:27:03 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/10 16:14:28 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Dog.hpp"

// Construtor padrão
Dog::Dog() : Animal("Dog") // Inicializa diretamente o tipo
{
    std::cout << BLUE << "Parameter constructor initialized. " << "Class Dog." << RESET << std::endl;
};

// Construtor com parâmetro
Dog::Dog(std::string name)
{
    this->_type = name;
    std::cout << BLUE << "Parameter constructor initialized. " << "Class Dog." << RESET << std::endl;
};

// Construtor de cópia
Dog::Dog(const Dog &copy) : Animal(copy) 
{
    this->_type = copy._type;
    std::cout << BLUE << "Copy constructor initialized. "
                         "Class Dog."
              << RESET << std::endl;
};

// Operador de atribuição
Dog &Dog::operator=(const Dog &src)
{
    if (this != &src) // Verifica auto-atribuição
    {
        this->_type = src._type;
    }
    std::cout  << BLUE << "Assignment operator called. Class Dog."<< RESET << std::endl;
    return *this;
};

Dog::~Dog()
{
     std::cout  << RED << "Destructor called. Class Dog."<< RESET << std::endl;
};

void Dog::makeSound() const 
{
    std::cout  << "HAUU HAUU. "  YELLOW << "Class Dog." << RESET << std::endl;
};
