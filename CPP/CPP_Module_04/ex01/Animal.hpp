/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:36:20 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:36:38 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>
# include <string>

class Animal
{
protected:
    std::string _type; // Tipo do animal

public:
    // Construtor padrão
    Animal();

    // Construtor de cópia
    Animal(const Animal& other);

    // Operador de atribuição
    Animal& operator=(const Animal& other);

    // Destrutor virtual
    virtual ~Animal();

    // Funções membros
    virtual void makeSound() const; // Método virtual para som
    std::string getType() const;
};

#endif
