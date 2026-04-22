/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:50:31 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 15:53:40 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria(std::string const &type) : _type(type)
{
    std::cout << GREEN << "AMateria de type " << _type << " créée !" << RESET << std::endl;
}

AMateria::~AMateria()
{
    std::cout << GREEN <<  "AMateria de type " << _type << " détruite !" << RESET << std::endl;
}

std::string const &AMateria::getType() const
{
    return _type;
}

void AMateria::use(ICharacter &target)
{
    std::cout << GREEN << "* Utilise AMateria sur le personnage " << RESET << target.getName() << " *" << std::endl;
}
