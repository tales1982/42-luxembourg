/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:40:51 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 15:40:48 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <string>
#include <iostream>

// Definindo as macros para as cores
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"  // Ciano
#define MAGENTA "\033[35m"  // Magenta
#define RESET   "\033[0m"   // Reseta a cor para o padrão

class WrongAnimal
{
protected:
    std::string type;

public:
    WrongAnimal();

    ~WrongAnimal();

    std::string getType() const;

    void makeSound() const;
};

#endif
