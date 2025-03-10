/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:51:24 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/10 10:33:16 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
    int i;
    
    i = 0;
    while ( i < 4 ){
        _sources[i] = 0;
        ++i;
    }
        
    std::cout << MAGENTA << "MateriaSource créé !" << RESET << std::endl;
}

MateriaSource::MateriaSource(MateriaSource const &other)
{
    int i;
    
    i= 0;
    while ( i < 4){
        _sources[i] = other._sources[i] ? other._sources[i]->clone() : 0;
        ++i;
    }
       
}

MateriaSource &MateriaSource::operator=(MateriaSource const &other)
{
    int i;
    
    i = 0;
    if (this != &other)
    {
        while ( i < 4 )
        {
            delete _sources[i];
            _sources[i] = other._sources[i] ? other._sources[i]->clone() : 0;
            ++i;
        }
    }
    return *this;
}

MateriaSource::~MateriaSource()
{
    int i;
    
    i = 0;
    while ( i < 4){
        delete _sources[i];
        ++i;
    }
        
    std::cout << MAGENTA << "MateriaSource détruit !" << RESET << std::endl;
}

void MateriaSource::learnMateria(AMateria *m)
{

    int i;
    
    i = 0;
    while ( i < 4)
    {
        if (!_sources[i])
        {
            _sources[i] = m;
            break;
        }
        ++i;
    }
}

AMateria *MateriaSource::createMateria(std::string const &type)
{
    int i;
    
    i = 0;
    while ( i < 4)
    {
        if (_sources[i] && _sources[i]->getType() == type)
            return _sources[i]->clone();
        ++i;
    }
    return 0;
}
