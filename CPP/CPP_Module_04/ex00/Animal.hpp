/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:19:21 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/10 20:10:53 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include <string>

// Definições de cores
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"


class Animal {
protected:
    std::string _type;

public:
    // Construtores
    Animal(); // Padrão
    Animal(std::string name); // Com parâmetro
    Animal(const Animal &copy); // Cópia

    // Operador de atribuição
    Animal &operator=(const Animal &src);

    // Destrutor
    virtual ~Animal();

    // Métodos adicionais
    virtual void makeSound() const;
    std::string getType() const;
};

#endif
