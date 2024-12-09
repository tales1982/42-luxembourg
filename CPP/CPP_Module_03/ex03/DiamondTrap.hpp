/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:57:44 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/09 17:33:10 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include "ClapTrap.hpp"
#include <iostream>
#include <string>

class DiamondTrap : public FragTrap, public ScavTrap {
private:
    std::string _name; // Nome privado específico do DiamondTrap

public:
    // Construtores e destrutores
    DiamondTrap();
    DiamondTrap(const std::string &name);
    DiamondTrap(const DiamondTrap &copy);
    ~DiamondTrap();

    // Operador de atribuição
    DiamondTrap &operator=(const DiamondTrap &src);

    // Métodos
    void whoAmI();
    using ScavTrap::attack; // Especifica que o método attack() vem do ScavTrap
};

#endif
