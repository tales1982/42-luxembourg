/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:27:18 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/10 16:14:20 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

// Construtor padrão
Cat::Cat() : Animal("Cat") // Inicializa diretamente o tipo
{
    std::cout << BLUE << "Parameter constructor initialized. " << "Class Cat." << RESET << std::endl;
};

// Construtor com parâmetro
Cat::Cat(std::string name)
{
    this->_type = name;
    std::cout << BLUE << "Parameter constructor initialized. " << "Class CAT." << RESET << std::endl;
};

// Construtor de cópia
Cat::Cat(const Cat &copy) : Animal(copy)
{
    this->_type = copy._type;
    std::cout << BLUE << "Copy constructor initialized. "
                         "Class CAT."
              << RESET << std::endl;
};

// Operador de atribuição
Cat &Cat::operator=(const Cat &src)
{
    if (this != &src) // Verifica auto-atribuição
    {
        this->_type = src._type;
    }
    std::cout  << BLUE << "Assignment operator called. Class Cat."<< RESET << std::endl;
    return *this;
};

Cat::~Cat()
{
     std::cout  << RED << "Destructor called. Class Cat."<< RESET << std::endl;
};

void Cat::makeSound() const 
{
    std::cout  << "Miau Miau. "  YELLOW << "Class Cat." << RESET << std::endl;
};