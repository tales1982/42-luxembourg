/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:03:09 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/05 13:03:10 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "Fixed.hpp"

// Inicializa a constante estática (definição)
const int Fixed::_fractionalBits = 8;

// Construtor padrão
Fixed::Fixed() : _value(0)
{
    std::cout << "Default constructor called" << std::endl;
}

// Construtor de cópia
Fixed::Fixed(const Fixed &other)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = other; // Chama o operador de atribuição
}

// Operador de atribuição
Fixed &Fixed::operator=(const Fixed &other)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other) { // Evita autoatribuição
        this->_value = other.getRawBits();
    }
    return *this; // Retorna a referência ao objeto atual
}

// Destrutor
Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

// Retorna o valor interno sem conversão
int Fixed::getRawBits(void) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return this->_value;
}

// Define o valor interno
void Fixed::setRawBits(int const raw)
{
    std::cout << "setRawBits member function called" << std::endl;
    this->_value = raw;
}
