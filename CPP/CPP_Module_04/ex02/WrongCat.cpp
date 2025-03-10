/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:40:56 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 15:51:42 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

// Constructeur
WrongCat::WrongCat()
{
    type = MAGENTA "WrongCat" RESET; // Définit le type comme "WrongCat"
    std::cout << MAGENTA << "Constructeur de WrongCat appelé !" << RESET << std::endl;
}

// Destructeur
WrongCat::~WrongCat()
{
    std::cout << MAGENTA << "Destructeur de WrongCat appelé !" << RESET << std::endl;
}
