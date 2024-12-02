/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 11:26:36 by tales             #+#    #+#             */
/*   Updated: 2024/12/01 12:06:58 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include<iostream>

class Weapon
{
private:
    std::string _type;
    
public:
    Weapon();
    Weapon(std:: string type);
    ~Weapon();
   
   	void setType(std::string type); // define  o  tipo  usando  o  novo  passado  como  parâmetro
	const std::string &getType() const; //retorna  uma  referência  const  ao  tipo
};




#endif