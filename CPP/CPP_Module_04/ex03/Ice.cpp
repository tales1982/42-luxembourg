/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:50:59 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:01:53 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice() : AMateria("ice")
{
    std::cout << RED << "Ice créé !" << RESET << std::endl;
}

Ice::Ice(Ice const &other) : AMateria(other)
{
    std::cout << RED << "Ice copié !" << RESET << std::endl;
}

Ice &Ice::operator=(Ice const &other)
{
    if (this != &other)
        _type = other._type;
    std::cout << RED << "Opérateur d'affectation de Ice appelé !" << RESET << std::endl;
    return *this;
}

Ice::~Ice()
{
    std::cout << RED << "Ice détruit !" << std::endl;
}

AMateria *Ice::clone() const
{
    return new Ice(*this);
}

void Ice::use(ICharacter &target)
{
    std::cout << RED << "* tire un éclair de glace sur " << target.getName() << " *" << RESET << std::endl;
}
