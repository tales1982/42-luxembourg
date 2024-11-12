/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:29:17 by tlima-de          #+#    #+#             */
/*   Updated: 2024/11/12 12:56:53 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>


class Zombie
{
private:
    /* data */
public:
    Zombie(/* args */);
    ~Zombie();
    Zombie* zombieHorde( int N, std::string name );
};

#endif