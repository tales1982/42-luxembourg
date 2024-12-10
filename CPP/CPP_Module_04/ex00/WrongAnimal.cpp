/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:53:02 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/10 16:01:45 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : _type("WrongAnimal") 
{
    
}

WrongAnimal::~WrongAnimal()
{
    
}

void WrongAnimal::makeSound() const 
{
     std::cout << "WrongAnimal sound!" << std::endl; 
}

