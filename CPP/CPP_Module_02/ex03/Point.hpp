/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:23:16 by sanweber          #+#    #+#             */
/*   Updated: 2024/12/05 13:49:56 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

// Classe para representar um ponto 2D
class Point
{
private:
    const Fixed _x; // Coordenada X (constante)
    const Fixed _y; // Coordenada Y (constante)

public:
    Point(); // Construtor padrão
    Point(const float x, const float y); // Construtor com parâmetros
    Point(const Point &other); // Construtor de cópia
    Point &operator=(const Point &other); // Operador de atribuição
    ~Point(); // Destrutor

    Fixed getX() const; // Obtém a coordenada X
    Fixed getY() const; // Obtém a coordenada Y
};

#endif
