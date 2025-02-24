/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:28:18 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:39:41 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure() : AMateria("cure")
{
    std::cout << "Cure criado!" << std::endl;
}

Cure::Cure(Cure const &other) : AMateria(other)
{
    std::cout << "Cure copiado!" << std::endl;
}

Cure &Cure::operator=(Cure const &other)
{
    if (this != &other) 
        _type = other._type;
    std::cout << "Operador de atribuição de Cure chamado!" << std::endl;
    return *this;
}

Cure::~Cure()
{
    std::cout << "Cure destruído!" << std::endl;
}

AMateria* Cure::clone() const
{
    return new Cure(*this);
}

void Cure::use(ICharacter& target)
{
    std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}
