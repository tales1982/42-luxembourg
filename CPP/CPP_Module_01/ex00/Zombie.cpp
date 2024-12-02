/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:30:36 by tlima-de          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/12/01 10:07:37 by tales            ###   ########.fr       */
=======
/*   Updated: 2024/11/22 19:50:55 by tales            ###   ########.fr       */
>>>>>>> b21490d1858790a17896a3ac2af906c3de60d84e
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

<<<<<<< HEAD
// Construtor para inicializar o nome do zumbi
Zombie:: Zombie(std::string _name)
{
    this->_name = _name;
    std::cout << "Zombie \"" << _name << "\" created" << std::endl;
=======
Zombie::Zombie(std::string name)
{
	this->_name = name;
	std::cout << "Zombie \"" << _name << "\" created" << std::endl;
>>>>>>> b21490d1858790a17896a3ac2af906c3de60d84e
}

// Função para anunciar
void Zombie::announce(void)
{
<<<<<<< HEAD
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

// Destrutor
Zombie:: ~Zombie()
{
    std::cout << _name << " is destroyed." << std::endl;
=======
	std::cout << "Zombie \"" << _name << "\" destroyed" << std::endl;
}

void Zombie::announce()
{
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
>>>>>>> b21490d1858790a17896a3ac2af906c3de60d84e
}
