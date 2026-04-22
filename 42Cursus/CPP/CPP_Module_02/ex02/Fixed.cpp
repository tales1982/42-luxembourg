/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:17:22 by sanweber          #+#    #+#             */
/*   Updated: 2024/12/05 13:44:19 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <cmath>

// Construtor padrão
Fixed::Fixed() : _value(0) {}

// Construtor que aceita um inteiro
Fixed::Fixed(const int num) {
    _value = num << _fractionalBits; // Multiplica o inteiro por 2^8
}

// Construtor que aceita um float
Fixed::Fixed(const float num) {
    _value = roundf(num * (1 << _fractionalBits)); // Multiplica o float por 2^8 e arredonda
}

// Construtor de cópia
Fixed::Fixed(const Fixed &other) {
    *this = other; // Reutiliza o operador de atribuição
}

// Destrutor
Fixed::~Fixed() {}

// Operador de atribuição
Fixed &Fixed::operator=(const Fixed &other) {
    if (this != &other) {
        _value = other._value;
    }
    return *this;
}

// Converte ponto fixo para float
float Fixed::toFloat() const {
    return (float)_value / (1 << _fractionalBits);
}

// Converte ponto fixo para inteiro
int Fixed::toInt() const {
    return _value >> _fractionalBits; // Divide por 2^8
}

// Retorna o valor bruto
int Fixed::getRawBits() const {
    return _value;
}

// Define o valor bruto
void Fixed::setRawBits(int const raw) {
    _value = raw;
}

// Sobrecarga dos operadores de comparação
bool Fixed::operator>(const Fixed &other) const {
    return _value > other._value;
}

bool Fixed::operator<(const Fixed &other) const {
    return _value < other._value;
}

bool Fixed::operator>=(const Fixed &other) const {
    return _value >= other._value;
}

bool Fixed::operator<=(const Fixed &other) const {
    return _value <= other._value;
}

bool Fixed::operator==(const Fixed &other) const {
    return _value == other._value;
}

bool Fixed::operator!=(const Fixed &other) const {
    return _value != other._value;
}

// Sobrecarga dos operadores aritméticos
Fixed Fixed::operator+(const Fixed &other) const {
    Fixed result;
    result.setRawBits(_value + other._value);
    return result;
}

Fixed Fixed::operator-(const Fixed &other) const {
    Fixed result;
    result.setRawBits(_value - other._value);
    return result;
}

Fixed Fixed::operator*(const Fixed &other) const {
    Fixed result;
    result.setRawBits((_value * other._value) >> _fractionalBits);
    return result;
}

Fixed Fixed::operator/(const Fixed &other) const {
    Fixed result;
    result.setRawBits((_value << _fractionalBits) / other._value);
    return result;
}

// Sobrecarga dos operadores de incremento/decremento
Fixed &Fixed::operator++() {
    ++_value;
    return *this;
}

Fixed Fixed::operator++(int) {
    Fixed temp = *this;
    ++_value;
    return temp;
}

Fixed &Fixed::operator--() {
    --_value;
    return *this;
}

Fixed Fixed::operator--(int) {
    Fixed temp = *this;
    --_value;
    return temp;
}

// Funções estáticas min e max
Fixed &Fixed::min(Fixed &a, Fixed &b) {
    return (a < b) ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
    return (a < b) ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
    return (a > b) ? a : b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
    return (a > b) ? a : b;
}

// Sobrecarga do operador de inserção
std::ostream &operator<<(std::ostream &out, const Fixed &fixed) {
    out << fixed.toFloat();
    return out;
}
