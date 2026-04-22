/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newZombie.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2024/11/30 19:51:50 by tales             #+#    #+#             */
/*   Updated: 2024/12/01 10:10:04 by tales            ###   ########.fr       */
=======
/*   Created: 2024/11/22 19:55:24 by tales             #+#    #+#             */
/*   Updated: 2024/11/22 20:07:30 by tales            ###   ########.fr       */
>>>>>>> b21490d1858790a17896a3ac2af906c3de60d84e
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

<<<<<<< HEAD
Zombie *newZombie(std::string name)
{
    return new Zombie(name);
}

/*
Outra opcao pra declarar a funcao:

Zombie *newZombie( std::string name )
{
    Zombie *newZombie;
    
    newZombie = new Zombie(name);
    return (newZombie);
}

*/
=======
Zombie *newZombie( std::string name )
{
	Zombie *newZombie;
	
	newZombie = new Zombie(name);
	return (newZombie);
}
>>>>>>> b21490d1858790a17896a3ac2af906c3de60d84e
