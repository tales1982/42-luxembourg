/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:23:05 by tales             #+#    #+#             */
/*   Updated: 2024/12/01 10:48:40 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie *zombieHorde(int N, std::string name)
{
    Zombie *zombies;
    
    zombies = new Zombie[N];

    for (size_t i = 0; i < N; i++)
    {
            zombies[i] = Zombie(name);
    }
    return (zombies);
    
}
