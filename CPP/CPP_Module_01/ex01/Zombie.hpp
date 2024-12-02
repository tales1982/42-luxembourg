/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:22:23 by tales             #+#    #+#             */
/*   Updated: 2024/12/01 10:49:50 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>
#include <iostream>

class Zombie {
private:
    std::string _name;

public:
    Zombie();                    // Construtor padrão
    Zombie(std::string name);    // Construtor com parâmetro
    ~Zombie();                   // Destrutor

    void announce(void);         // Função para anunciar o zumbi
};

Zombie *zombieHorde(int N, std::string name);


#endif
