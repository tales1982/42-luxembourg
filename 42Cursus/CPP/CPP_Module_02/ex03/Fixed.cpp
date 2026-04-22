/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:22:15 by sanweber          #+#    #+#             */
/*   Updated: 2024/12/05 13:48:58 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

// Construtor padrão
Fixed::Fixed() : _value(0) {}

// Construtor que recebe um inteiro
Fixed::Fixed(const int intValue) {
    _value = intValue << _fractionalBits; // Converte para ponto fixo
}

// Construtor que recebe um float
Fixed::Fixed(const float floatValue) {
    _value = roundf(floatValue * (1 << _fractionalBits)); // Converte para ponto fixo
}

// Construtor de cópia
Fixed::Fixed(const Fixed &other) {
    *this = other; // Usa o operador de atribuição
}

// Operador de atribuição
Fixed &Fixed::operator=(const Fixed &other) {
    if (this != &other) {
        _value = other._value;
    }
    return *this;
}

// Destrutor
Fixed::~Fixed() {}

// Obtém o valor bruto
int Fixed::getRawBits() const {
    return _value;
}

// Define o valor bruto
void Fixed::setRawBits(int const raw) {
    _value = raw;
}

// Converte para float
float Fixed::toFloat() const {
    return (float)_value / (1 << _fractionalBits);
}

// Converte para inteiro
int Fixed::toInt() const {
    return _value >> _fractionalBits;
}

// Sobrecarga de operadores aritméticos
Fixed Fixed::operator+(const Fixed &other) const {
    return Fixed(this->toFloat() + other.toFloat());
}

Fixed Fixed::operator-(const Fixed &other) const {
    return Fixed(this->toFloat() - other.toFloat());
}

Fixed Fixed::operator*(const Fixed &other) const {
    return Fixed(this->toFloat() * other.toFloat());
}

Fixed Fixed::operator/(const Fixed &other) const {
    return Fixed(this->toFloat() / other.toFloat());
}

// Sobrecarga de operadores de comparação
bool Fixed::operator>(const Fixed &other) const {
    return this->_value > other._value;
}

bool Fixed::operator<(const Fixed &other) const {
    return this->_value < other._value;
}

bool Fixed::operator>=(const Fixed &other) const {
    return this->_value >= other._value;
}

bool Fixed::operator<=(const Fixed &other) const {
    return this->_value <= other._value;
}

bool Fixed::operator==(const Fixed &other) const {
    return this->_value == other._value;
}

bool Fixed::operator!=(const Fixed &other) const {
    return this->_value != other._value;
}

// Sobrecarga do operador de saída
std::ostream &operator<<(std::ostream &out, const Fixed &value) {
    out << value.toFloat();
    return out;
}
