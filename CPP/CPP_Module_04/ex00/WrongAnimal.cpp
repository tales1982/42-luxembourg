/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:53:02 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/10 20:01:31 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
{
    this->_type = "WrongAnimal";
    std::cout << BLUE << "Default constructor initialized. Class WrongAnimal. "<< RESET << std::endl;
    
}

WrongAnimal::WrongAnimal(std::string name)
{
     this->_type = name;
    std::cout  << BLUE << "Parameter constructor initialized. Class WrongAnimal."<< RESET << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &copy) : _type(copy._type)
{
    std::cout << BLUE << "Copy constructor initialized. Class WrongAnimal."<< RESET << std::endl;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &src)
{
    if (this != &src) // Verifica auto-atribuição
    {
        this->_type = src._type;
    }
    std::cout  << BLUE << "Assignment operator called. Class WrongAnimal."<< RESET << std::endl;
    return *this;
}

WrongAnimal::~WrongAnimal()
{
    std::cout  << RED << "Destructor called. Class WrongAnimal."<< RESET << std::endl;
}

void WrongAnimal::makeSound() const 
{
     std::cout << "WrongAnimal sound!" << std::endl; 
}

