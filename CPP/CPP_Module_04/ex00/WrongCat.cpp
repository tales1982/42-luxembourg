/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:52:40 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/10 16:07:41 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"WrongCat.hpp"


WrongCat::WrongCat() 
{ 
    _type = "WrongCat"; 
}

WrongCat::~WrongCat()
{
    
}

void WrongCat::makeSound() const 
{ 
    std::cout << "WrongCat sound!" << std::endl; 
}