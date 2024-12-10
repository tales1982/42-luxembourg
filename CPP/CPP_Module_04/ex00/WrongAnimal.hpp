/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:52:13 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/10 19:36:46 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <iostream>
#include <string>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

class WrongAnimal
{
protected:
    std::string _type;

public:
    WrongAnimal();                             // padrao
    WrongAnimal(std::string name);             // com parametros
    WrongAnimal(const WrongAnimal &copy);           // copia ex; A = B obj A recerber dados obj B
    WrongAnimal &operator=(const WrongAnimal &src); // Overloaded Operators

    // destructor
    ~WrongAnimal();
    void makeSound() const;
    std::string getType(void)const;
};

#endif