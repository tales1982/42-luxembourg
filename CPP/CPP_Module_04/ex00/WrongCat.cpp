/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:52:40 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/10 20:17:00 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

// Construtor padrão
WrongCat::WrongCat() : WrongAnimal()
{
    std::cout << BLUE <<"Default constructor initialized. Class WrongCat."<< RESET << std::endl;
}

// Construtor com parâmetro
WrongCat::WrongCat(std::string name) : WrongAnimal(name)
{
    std::cout << "Parameter constructor initialized. Class WrongCat." << std::endl;
}

// Construtor de cópia
WrongCat::WrongCat(const WrongCat &copy) : WrongAnimal(copy)
{
    std::cout << "Copy constructor initialized. Class WrongCat." << std::endl;
}

// Operador de atribuição
WrongCat &WrongCat::operator=(const WrongCat &src)
{
    if (this != &src) // Evitar auto-atribuição
    {
        WrongAnimal::operator=(src); // Chama o operador de atribuição da classe base
    }
    std::cout << "Assignment operator called. Class WrongCat." << std::endl;
    return *this;
}

// Destrutor
WrongCat::~WrongCat()
{
    std::cout << RED << "Destructor called. Class WrongCat." << RESET << std::endl;
}

// Método makeSound
void WrongCat::makeSound() const
{
    std::cout << "WrongCat sound!" << std::endl;
}
