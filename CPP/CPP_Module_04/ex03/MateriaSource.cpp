/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:38:19 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:40:21 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
    for (int i = 0; i < 4; ++i)
        _sources[i] = 0;
    std::cout << "MateriaSource criado!" << std::endl;
}

MateriaSource::MateriaSource(MateriaSource const &other)
{
    for (int i = 0; i < 4; ++i)
        _sources[i] = other._sources[i] ? other._sources[i]->clone() : 0;
}

MateriaSource &MateriaSource::operator=(MateriaSource const &other)
{
    if (this != &other)
   	{
        for (int i = 0; i < 4; ++i)
	   	{
            delete _sources[i];
            _sources[i] = other._sources[i] ? other._sources[i]->clone() : 0;
        }
    }
    return *this;
}

MateriaSource::~MateriaSource()
{
    for (int i = 0; i < 4; ++i)
        delete _sources[i];
    std::cout << "MateriaSource destruído!" << std::endl;
}

void MateriaSource::learnMateria(AMateria* m)
{
    for (int i = 0; i < 4; ++i)
   	{
        if (!_sources[i])
	   	{
            _sources[i] = m;
            break;
        }
    }
}

AMateria* MateriaSource::createMateria(std::string const &type)
{
    for (int i = 0; i < 4; ++i)
   	{
        if (_sources[i] && _sources[i]->getType() == type)
            return _sources[i]->clone();
    }
    return 0;
}
