/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:18:43 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:37:08 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
    // Criando um array de animais
    Animal* animals[4];

    // Metade Dogs e metade Cats
    for (int i = 0; i < 2; i++)
        animals[i] = new Dog();
    for (int i = 2; i < 4; i++)
        animals[i] = new Cat();

    // Exibindo sons dos animais
    for (int i = 0; i < 4; i++)
        animals[i]->makeSound();

    // Limpando memória
    for (int i = 0; i < 4; i++)
        delete animals[i];

    const WrongAnimal* wrongMeta = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();
    std::cout << wrongCat->getType() << " " << std::endl;
    wrongMeta->makeSound(); // Som genérico de WrongAnimal
    wrongCat->makeSound();  // Som genérico de WrongAnimal, não foi sobrescrito
    delete wrongMeta;
    delete wrongCat;

    return 0;
}