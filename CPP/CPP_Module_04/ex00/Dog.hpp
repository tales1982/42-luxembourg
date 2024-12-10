/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:27:11 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/10 19:35:00 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"

class Dog : public Animal
{
private:
    // Private Members
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