/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:49:13 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/05 15:28:18 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

// Declarações das funções em bsp.cpp
Fixed calculateArea(const Point &a, const Point &b, const Point &c);
bool bsp(Point const a, Point const b, Point const c, Point const point);

int main()
{
    Point a(0, 0);
    Point b(4, 0);
    Point c(0, 4);
    Point point(5, 2);

    if (bsp(a, b, c, point))
        std::cout << "O ponto está dentro do triângulo." << std::endl;
    else
        std::cout << "O ponto está fora do triângulo." << std::endl;
    return 0;
}
