/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:19:04 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:39:29 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# include <string>
# include <iostream>
# include "ICharacter.hpp"

// Classe abstrata AMateria
class AMateria
{
protected:
    std::string _type; // Tipo da matéria

public:
    // Construtor padrão com tipo
    AMateria(std::string const &type);

    // Destrutor virtual
    virtual ~AMateria();

    // Retorna o tipo da matéria
    std::string const &getType() const;

    // Método puro virtual para clonar a matéria
    virtual AMateria* clone() const = 0;

    // Usa a matéria em um personagem
    virtual void use(ICharacter& target);
};

#endif
