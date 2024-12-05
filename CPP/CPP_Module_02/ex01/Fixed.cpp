/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:13:08 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/05 13:42:34 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

// Construtor padrão
Fixed::Fixed() : _value(0)
{
    //std::cout << "DEBUG[1]" << std::endl;
    std::cout << "Default constructor called" << std::endl;
}

// Construtor que aceita um inteiro
Fixed::Fixed(int const num)
{
    //std::cout << "DEBUG[2]" << std::endl;
    std::cout << "Int constructor called" << std::endl;
    _value = num << _fractionalBits; // Converte inteiro para ponto fixo
}

// Construtor que aceita um float
Fixed::Fixed(float const num)
{
    //std::cout << "DEBUG[3]" << std::endl;
    std::cout << "Float constructor called" << std::endl;
    _value = roundf(num * (1 << _fractionalBits)); // Convert float a ponto fixo
}

// Construtor de cópia
Fixed::Fixed(Fixed const &other)
{
    //std::cout << "DEBUG[4]" << std::endl;
    std::cout << "Copy constructor called" << std::endl;
    *this = other; // Usa o operador de atribuição
}

// Operador de atribuição
Fixed &Fixed::operator=(Fixed const &other)
{
    //std::cout << "DEBUG[5]" << std::endl;
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)
        _value = other._value;
    return *this;
}

// Destrutor
Fixed::~Fixed()
{
    //std::cout << "DEBUG[6]" << std::endl;
    std::cout << "Destructor called" << std::endl;
}

// Converte o valor em ponto fixo para float
float Fixed::toFloat(void) const
{
    //std::cout << "DEBUG[7]" << std::endl;
    return static_cast<float>(_value) / (1 << _fractionalBits);
}

// Converte o valor em ponto fixo para inteiro
int Fixed::toInt(void) const
{
    //std::cout << "DEBUG[8]" << std::endl;
    return _value >> _fractionalBits;
}

// Get para o valor bruto
int Fixed::getRawBits(void) const
{
    //std::cout << "DEBUG[9]" << std::endl;
    return _value;
}

// Set para o valor bruto
void Fixed::setRawBits(int const raw)
{
    //std::cout << "DEBUG[10]" << std::endl;
    _value = raw;
}

// Sobrecarga do operador de inserção para o fluxo de saída
std::ostream &operator<<(std::ostream &out, Fixed const &fixed)
{
    //std::cout << "DEBUG[11]" << std::endl;
    out << fixed.toFloat(); // Exibe o valor em formato de ponto flutuante
    return out;
}