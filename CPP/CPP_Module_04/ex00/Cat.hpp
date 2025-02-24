/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:26:37 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:35:33 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"

class Cat : public Animal
{
public:
    // Construtor padrão
    Cat();

    // Construtor de cópia
    Cat(const Cat& other);

    // Operador de atribuição
    Cat& operator=(const Cat& other);

    // Destrutor
    ~Cat();

    // Sobrescrevendo o método makeSound
    void makeSound() const;
};

#endif
