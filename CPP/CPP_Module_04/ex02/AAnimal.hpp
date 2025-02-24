/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:36:20 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:38:00 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AANIMAL_HPP
# define AANIMAL_HPP

# include <iostream>
# include <string>

class AAnimal
{
protected:
    std::string _type; // Tipo do animal

public:
    // Construtor padrão
    AAnimal();

    // Construtor de cópia
    AAnimal(const AAnimal& other);

    // Operador de atribuição
    AAnimal& operator=(const AAnimal& other);

    // Destrutor virtual
    virtual ~AAnimal();

    // Funções membros
    virtual void makeSound() const = 0; // Método virtual p/ classe abstrata
    std::string getType() const;
};

#endif
