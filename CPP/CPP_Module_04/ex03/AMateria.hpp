/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:50:35 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 15:52:11 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <string>
#include <iostream>
#include "ICharacter.hpp"

// Definindo as macros para as cores
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"  // Ciano
#define MAGENTA "\033[35m"  // Magenta
#define RESET   "\033[0m"   // Reseta a cor para o padrão

class AMateria
{
protected:
    std::string _type;

public:
    AMateria(std::string const &type);

    virtual ~AMateria();

    std::string const &getType() const;

    virtual AMateria *clone() const = 0;

    virtual void use(ICharacter &target);
};

#endif
