/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:02:54 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/09 13:14:43 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"
#include <iostream>
#include <string>

class ScavTrap : public ClapTrap
{
private:
public:
    // Constructors
    ScavTrap();
    ScavTrap(const ScavTrap &copy); // cria uma copia do objeto
    ScavTrap(const std::string &name);
    ~ScavTrap();
    ScavTrap &operator=(const ScavTrap &src);

    // Public Methods
    void attack(const std::string &target);
    void guardGate();
};

#endif