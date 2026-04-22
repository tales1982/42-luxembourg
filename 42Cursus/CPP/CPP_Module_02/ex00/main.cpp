/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:25:16 by sanweber          #+#    #+#             */
/*   Updated: 2024/12/05 13:03:21 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main(void)
{
    Fixed a;         // Construtor padrão chamado
    Fixed b(a);      // Construtor de cópia chamado
    Fixed c;         // Construtor padrão chamado
    c = b;           // Operador de atribuição chamado

    std::cout << a.getRawBits() << std::endl; // Chamando getRawBits
    std::cout << b.getRawBits() << std::endl; // Chamando getRawBits
    std::cout << c.getRawBits() << std::endl; // Chamando getRawBits
    return 0;
}
