/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:13:01 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/05 13:18:26 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath> // Para a função roundf

class Fixed
{
private:
    int _value; // Armazena o valor em ponto fixo
    static const int _fractionalBits = 8; // Número de bits fracionários

public:
    // Construtor padrão
    Fixed();
    // Construtor que aceita um inteiro
    Fixed(int const num);
    // Construtor que aceita um float
    Fixed(float const num);
    // Construtor de cópia
    Fixed(Fixed const &other);
    // Operador de atribuição
    Fixed &operator=(Fixed const &other);
    // Destrutor
    ~Fixed();
    // Converte o valor em ponto fixo para float
    float toFloat(void) const;
    // Converte o valor em ponto fixo para inteiro
    int toInt(void) const;
    // Getter para obter o valor bruto (em ponto fixo)
    int getRawBits(void) const;
    // Setter para definir o valor bruto (em ponto fixo)
    void setRawBits(int const raw);
    // Sobrecarga do operador de inserção para o fluxo de saída
    friend std::ostream &operator<<(std::ostream &out, Fixed const &fixed);
};

#endif
