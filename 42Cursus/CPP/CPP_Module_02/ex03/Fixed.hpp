/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:25:06 by sanweber          #+#    #+#             */
/*   Updated: 2024/12/05 13:49:03 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed
{
private:
    int _value; // Valor armazenado em formato de ponto fixo
    static const int _fractionalBits = 8; // Número de bits para a parte fracionária

public:
    Fixed(); // Construtor padrão
    Fixed(const int intValue); // Construtor para inteiro
    Fixed(const float floatValue); // Construtor para float
    Fixed(const Fixed &other); // Construtor de cópia
    Fixed &operator=(const Fixed &other); // Operador de atribuição
    ~Fixed(); // Destrutor

    int getRawBits() const; // Obtém o valor bruto em ponto fixo
    void setRawBits(int const raw); // Define o valor bruto

    float toFloat() const; // Converte para float
    int toInt() const; // Converte para inteiro

    // Sobrecarga de operadores aritméticos
    Fixed operator+(const Fixed &other) const;
    Fixed operator-(const Fixed &other) const;
    Fixed operator*(const Fixed &other) const;
    Fixed operator/(const Fixed &other) const;

    // Sobrecarga de operadores de comparação
    bool operator>(const Fixed &other) const;
    bool operator<(const Fixed &other) const;
    bool operator>=(const Fixed &other) const;
    bool operator<=(const Fixed &other) const;
    bool operator==(const Fixed &other) const;
    bool operator!=(const Fixed &other) const;
};

// Sobrecarga do operador de saída para exibir valores em ponto fixo
std::ostream &operator<<(std::ostream &out, const Fixed &value);

#endif
