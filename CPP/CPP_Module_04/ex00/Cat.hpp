/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:27:28 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/10 14:20:03 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_PP
#define CAT_HPP

#include <iostream>
#include <string>
#include "Animal.hpp"

class Cat: public Animal
{
private:
public:
    Cat();                          // padrao
    Cat(std::string name);          // com parametros
    Cat(const Cat &copy);           // copia ex; A = B obj A recerber dados obj B
    Cat &operator=(const Cat &src); // copia por operador

    // destructor
    ~Cat();
    void makeSound()const;
};

#endif