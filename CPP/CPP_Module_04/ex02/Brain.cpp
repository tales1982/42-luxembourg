/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:40:07 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:14:00 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
	std::cout << BLUE << "Constructeur de Brain appelé !" << RESET << std::endl;
	for (int i = 0; i < 100; i++)
		ideas[i] = "Empty";
}

Brain::Brain(const Brain &other)
{
	std::cout << BLUE << "Constructeur de copie de Brain appelé !" << RESET << std::endl;
	for (int i = 0; i < 100; i++)
		ideas[i] = other.ideas[i];
}

Brain &Brain::operator=(const Brain &other)
{
	std::cout << BLUE << "Opérateur d'affectation de Brain appelé !" << RESET << std::endl;
	if (this != &other)
	{
		for (int i = 0; i < 100; i++)
			ideas[i] = other.ideas[i];
	}
	return (*this);
}

Brain::~Brain()
{
	std::cout << BLUE << "Destructeur de Brain appelé !" << RESET << std::endl;
}

void Brain::setIdea(int index, const std::string &idea)
{
	if (index >= 0 && index < 100)
		ideas[index] = idea;
}

std::string Brain::getIdea(int index) const
{
	if (index >= 0 && index < 100)
		return (ideas[index]);
	return ("");
}
