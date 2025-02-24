/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:33:14 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:39:33 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "ICharacter.hpp"

Character::Character(std::string const &name) : _name(name)
{
    for (int i = 0; i < 4; ++i)
        _inventory[i] = 0;
    std::cout << "Character " << _name << " criado!" << std::endl;
}

Character::Character(Character const &other) : _name(other._name)
{
    for (int i = 0; i < 4; ++i)
        _inventory[i] = other._inventory[i] ? other._inventory[i]->clone() : 0;
    std::cout << "Character copiado!" << std::endl;
}

Character &Character::operator=(Character const &other)
{
    if (this != &other)
   	{
        _name = other._name;
        for (int i = 0; i < 4; ++i)
	   	{
            delete _inventory[i];
            _inventory[i] = other._inventory[i] ? other._inventory[i]->clone() : 0;
        }
    }
    std::cout << "Operador de atribuição de Character chamado!" << std::endl;
    return *this;
}

Character::~Character()
{
    for (int i = 0; i < 4; ++i)
        delete _inventory[i];
    std::cout << "Character " << _name << " destruído!" << std::endl;
}

std::string const &Character::getName() const
{
    return _name;
}

void Character::equip(AMateria* m)
{
    for (int i = 0; i < 4; ++i)
   	{
        if (!_inventory[i])
	   	{
            _inventory[i] = m;
            break;
        }
    }
}

void Character::unequip(int idx)
{
    if (idx >= 0 && idx < 4)
        _inventory[idx] = 0;
}

void Character::use(int idx, ICharacter& target)
{
    if (idx >= 0 && idx < 4 && _inventory[idx])
        _inventory[idx]->use(target);
}
