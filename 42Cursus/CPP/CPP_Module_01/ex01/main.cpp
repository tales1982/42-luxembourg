/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:22:10 by tales             #+#    #+#             */
/*   Updated: 2024/12/01 10:49:02 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
	Zombie *horde;
	int N = 3;
	
	horde = zombieHorde(N, "Horde");
 	for (int i = 0; i < N; i++)
	{
       std::cout << "Index " << i << ": ";
	   horde[i].announce();
    }

	delete[] horde;
	return (0);
}