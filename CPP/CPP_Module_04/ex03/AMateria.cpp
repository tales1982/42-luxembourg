/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:20:52 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:39:24 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria(std::string const &type) : _type(type)
{
    std::cout << "AMateria do tipo " << _type << " criada!" << std::endl;
}

AMateria::~AMateria()
{
    std::cout << "AMateria do tipo " << _type << " destruída!" << std::endl;
}

std::string const &AMateria::getType() const
{
    return _type;
}

void AMateria::use(ICharacter& target)
{
    std::cout << "* Usa AMateria no personagem " << target.getName() << " *" << std::endl;
}
