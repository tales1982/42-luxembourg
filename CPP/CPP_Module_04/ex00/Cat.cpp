/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:27:18 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/10 20:17:51 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Cat.hpp"

// Construtor padrão
Cat::Cat() : Animal() // Inicializa diretamente o tipo
{
    this->_type = "Cat";
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
    std::cout << BLUE << "Copy constructor initialized. Class CAT."<< RESET << std::endl;
                         
             
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
    std::cout << YELLOW << this->getType() << " says: **Meeeoow**" << RESET << std::endl;
};