/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:34:48 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:38:45 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# include <string>
# include <iostream>

class WrongAnimal
{
protected:
    std::string type; // Tipo do animal

public:
    // Construtor padrão
    WrongAnimal();

    // Destrutor
    ~WrongAnimal();

    // Função para obter o tipo do animal
    std::string getType() const;

    // Método para emitir som
    void makeSound() const;
};

#endif
