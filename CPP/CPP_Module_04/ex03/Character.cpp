/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:50:39 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/10 10:24:49 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "ICharacter.hpp"

Character::Character(std::string const &name) : _name(name)
{
    int i;

    i = 0;
    while (i < 4)
    { _inventory[i] = 0;
        i++;
    }   
    std::cout << BLUE << "Character " << _name << " créé !" << RESET << std::endl;
}

Character::Character(Character const &other) : _name(other._name)
{
    int i;

    i = 0;
    while (i < 4){
        _inventory[i] = other._inventory[i] ? other._inventory[i]->clone() : 0;
        i++;
    }
    std::cout << BLUE << "Character copié !" << RESET << std::endl;
}

Character &Character::operator=(Character const &other)
{
    int i;

    i = 0;
    if (this != &other)
    {
        _name = other._name;
        while(i < 4)
        {
            delete _inventory[i];
            _inventory[i] = other._inventory[i] ? other._inventory[i]->clone() : 0;
            i++;
        }
    }
    std::cout << BLUE << "Opérateur d'affectation de Character appelé !" << RESET << std::endl;
    return *this;
}

Character::~Character()
{ 
    int i;

    i = 0;
    while (  i < 4 ){
        delete _inventory[i];
        ++i;
    }
    std::cout << BLUE << "Character " << _name << " détruit !" << RESET << std::endl;
}

std::string const &Character::getName() const
{
    return _name;
}

void Character::equip(AMateria *m)
{
    int i;
    
    i = 0;
    while ( i < 4 )
    {
        if (!_inventory[i])
        {
            _inventory[i] = m;
            break;
        }
        i++;
    }
}

void Character::unequip(int idx)
{
    if (idx >= 0 && idx < 4)
        _inventory[idx] = 0;
}

void Character::use(int idx, ICharacter &target)
{
    if (idx >= 0 && idx < 4 && _inventory[idx])
        _inventory[idx]->use(target);
}
