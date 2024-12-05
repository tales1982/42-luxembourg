/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:25:07 by sanweber          #+#    #+#             */
/*   Updated: 2024/12/05 13:48:52 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

// Calcula a área de um triângulo usando os vértices
Fixed calculateArea(const Point &a, const Point &b, const Point &c)
{
    float area = ((a.getX() * (b.getY() - c.getY())).toFloat() +
                  (b.getX() * (c.getY() - a.getY())).toFloat() +
                  (c.getX() * (a.getY() - b.getY())).toFloat()) / 2.0f;
	return Fixed(area < 0 ? -area : area); // retorna area absoluta
}

// Função para verificar se o ponto está dentro do triângulo
bool bsp(Point const a, Point const b, Point const c, Point const point)
{
    Fixed areaABC = calculateArea(a, b, c);
    Fixed areaPAB = calculateArea(point, a, b);
    Fixed areaPBC = calculateArea(point, b, c);
    Fixed areaPCA = calculateArea(point, c, a);

	Fixed tolerance = Fixed(0.01f); // margem de erro

    return fabs((areaPAB + areaPBC + areaPCA - areaABC).toFloat()) < tolerance.toFloat();
}
