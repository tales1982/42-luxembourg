/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:29:17 by tlima-de          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/12/01 10:06:48 by tales            ###   ########.fr       */
=======
/*   Updated: 2024/11/22 19:49:50 by tales            ###   ########.fr       */
>>>>>>> b21490d1858790a17896a3ac2af906c3de60d84e
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <string>
#include <iostream>
<<<<<<< HEAD
=======
#include <new>
>>>>>>> b21490d1858790a17896a3ac2af906c3de60d84e

class Zombie
{
private:
<<<<<<< HEAD
    std::string _name;

public:
    Zombie(std::string _name);
    ~Zombie();
    void announce(void);
    
};

    Zombie *newZombie(std::string name);
    void randomChump(std::string name);
    
=======
	std::string _name;
public:
	Zombie(std::string name);
	~Zombie();

	void announce(void);
};

void randomChump(std::string name);
Zombie *newZombie(std::string name);

>>>>>>> b21490d1858790a17896a3ac2af906c3de60d84e
#endif