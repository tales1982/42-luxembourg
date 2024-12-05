/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:10:44 by sanweber          #+#    #+#             */
/*   Updated: 2024/12/05 13:44:27 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed {
private:
    int _value;                           // Valor do número em formato de ponto fixo
    static const int _fractionalBits = 8; // Número de bits para a parte fracionária

public:
    Fixed();                              // Construtor padrão
    Fixed(const int num);                 // Construtor que aceita um número inteiro
    Fixed(const float num);               // Construtor que aceita um número float
    Fixed(const Fixed &other);            // Construtor de cópia
    ~Fixed();                             // Destrutor

    Fixed &operator=(const Fixed &other); // Operador de atribuição

    int getRawBits() const;               // Retorna o valor bruto (ponto fixo)
    void setRawBits(int const raw);       // Define o valor bruto (ponto fixo)

    float toFloat() const;                // Converte ponto fixo para float
    int toInt() const;                    // Converte ponto fixo para inteiro

    // Sobrecarga dos operadores de comparação
    bool operator>(const Fixed &other) const;
    bool operator<(const Fixed &other) const;
    bool operator>=(const Fixed &other) const;
    bool operator<=(const Fixed &other) const;
    bool operator==(const Fixed &other) const;
    bool operator!=(const Fixed &other) const;

    // Sobrecarga dos operadores aritméticos
    Fixed operator+(const Fixed &other) const;
    Fixed operator-(const Fixed &other) const;
    Fixed operator*(const Fixed &other) const;
    Fixed operator/(const Fixed &other) const;

    // Sobrecarga dos operadores de pré/pós-incrementação e decrementação
    Fixed &operator++();   // Pré-incrementação
    Fixed operator++(int); // Pós-incrementação
    Fixed &operator--();   // Pré-decrementação
    Fixed operator--(int); // Pós-decrementação

    // Funções estáticas min e max
    static Fixed &min(Fixed &a, Fixed &b);
    static const Fixed &min(const Fixed &a, const Fixed &b);
    static Fixed &max(Fixed &a, Fixed &b);
    static const Fixed &max(const Fixed &a, const Fixed &b);
};

// Sobrecarga do operador de inserção
std::ostream &operator<<(std::ostream &out, const Fixed &fixed);

#endif
