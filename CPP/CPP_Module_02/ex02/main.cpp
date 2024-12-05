/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:06:16 by sanweber          #+#    #+#             */
/*   Updated: 2024/12/05 13:44:37 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Fixed.hpp"

int main()
{
    Fixed a;                                // Construtor padrão
    Fixed const b(Fixed(5.05f) * Fixed(2)); // Construtores float, int, multiply

    std::cout << a << std::endl;                // 0
    std::cout << ++a << std::endl;              // Pré-incremento: 0.00390625
    std::cout << a << std::endl;                // 0.00390625
    std::cout << a++ << std::endl;              // Pós-incremento: 0.00390625
    std::cout << a << std::endl;                // 0.0078125
    std::cout << b << std::endl;                // 10.1016
    std::cout << Fixed::max(a, b) << std::endl; // 10.1016
    return 0;
}
