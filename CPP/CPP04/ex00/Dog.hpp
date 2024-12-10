/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:27:11 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/10 15:50:54 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DOG_HPP
#define DOG_HPP

#include <iostream>
#include <string>
#include "Animal.hpp"

class Dog : public Animal
{
private:
public:
    Dog();                          // padrao
    Dog(std::string name);          // com parametros
    Dog(const Dog &copy);           // copia ex; A = B obj A recerber dados obj B
    Dog &operator=(const Dog &src); // copia por operador

    // destructor
    ~Dog();
    void makeSound()const;
};

#endif