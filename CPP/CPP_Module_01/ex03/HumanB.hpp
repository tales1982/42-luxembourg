/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 11:27:44 by tales             #+#    #+#             */
/*   Updated: 2024/12/01 12:39:53 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP

#include "Weapon.hpp"
#include <string>
#include <iostream>

class HumanB
{
	private:
		std::string _name;
		Weapon *_weapon;
	public:
		
		HumanB(std::string name);
		~HumanB();

		
		void attack();
		void setWeapon(Weapon &weapon);
};

#endif