/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:30:47 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:35:42 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"

class Dog : public Animal
{
public:
    // Construtor padrão
    Dog();

    // Construtor de cópia
    Dog(const Dog& other);

    // Operador de atribuição
    Dog& operator=(const Dog& other);

    // Destrutor
    ~Dog();

    // Sobrescrevendo o método makeSound
    void makeSound() const;
};

#endif
