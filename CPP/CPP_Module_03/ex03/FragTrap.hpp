/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:26:46 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/09 17:32:06 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"
#include <iostream>
#include <string>

class FragTrap : virtual public ClapTrap
{
private:

public:
    // Constructors
    FragTrap();
    FragTrap(const FragTrap &copy); // cria uma copia do objeto
    FragTrap(const std::string &name);
    virtual ~FragTrap();
    FragTrap &operator=(const FragTrap &src);

    // Public Methods
    void highFivesGuys(void);

};

#endif