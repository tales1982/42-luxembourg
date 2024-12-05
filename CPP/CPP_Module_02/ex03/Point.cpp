/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:24:16 by sanweber          #+#    #+#             */
/*   Updated: 2024/12/05 13:49:29 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

// Construtor padrão
Point::Point() : _x(0), _y(0) {}

// Construtor com parâmetros
Point::Point(const float x, const float y) : _x(x), _y(y) {}

// Construtor de cópia
Point::Point(const Point &other) : _x(other._x), _y(other._y) {}

// Operador de atribuição
Point &Point::operator=(const Point &other)
{
    (void)other; // Como os membros são constantes, não podem ser reatribuídos
    return *this;
}

// Destrutor
Point::~Point() {}

// Obtém a coordenada X
Fixed Point::getX() const
{
    return _x;
}

// Obtém a coordenada Y
Fixed Point::getY() const
{
    return _y;
}
