/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:50:51 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:02:42 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure() : AMateria("cure")
{
    std::cout << YELLOW << "Cure créé !" << RESET << std::endl;
}

Cure::Cure(Cure const &other) : AMateria(other)
{
    std::cout << YELLOW << "Cure copié !" << RESET << std::endl;
}

Cure &Cure::operator=(Cure const &other)
{
    if (this != &other)
        _type = other._type;
    std::cout << YELLOW << "Opérateur d'affectation de Cure appelé !" << RESET << std::endl;
    return *this;
}

Cure::~Cure()
{
    std::cout << YELLOW << "Cure détruit !" << RESET << std::endl;
}

AMateria *Cure::clone() const
{
    return new Cure(*this);
}

void Cure::use(ICharacter &target)
{
    std::cout << YELLOW << "* soigne les blessures de " << target.getName() << " *" << RESET << std::endl;
}
