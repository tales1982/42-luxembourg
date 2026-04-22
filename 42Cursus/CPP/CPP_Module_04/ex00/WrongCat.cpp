/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:13:44 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:06:49 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat()
{
	type = MAGENTA "WrongCat" RESET;
	std::cout << MAGENTA << "Constructeur de WrongCat appelé !" << RESET << std::endl;
}

WrongCat::~WrongCat()
{
	std::cout << MAGENTA << "Destructeur de WrongCat appelé !" << RESET << std::endl;
}
