/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:30:36 by tlima-de          #+#    #+#             */
/*   Updated: 2024/11/22 19:50:55 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(std::string name)
{
	this->_name = name;
	std::cout << "Zombie \"" << _name << "\" created" << std::endl;
}

Zombie::~Zombie()
{
	std::cout << "Zombie \"" << _name << "\" destroyed" << std::endl;
}

void Zombie::announce()
{
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

