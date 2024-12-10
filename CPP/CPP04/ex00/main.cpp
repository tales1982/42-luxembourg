/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:18:41 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/10 15:51:47 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;

    i->makeSound(); // Deve emitir o som de gato
    j->makeSound(); // Deve emitir o som de cachorro

    delete j;
    delete i;

    // Teste de WrongAnimal
    const WrongAnimal* wa = new WrongCat();
    wa->makeSound(); // Deve emitir o som de WrongAnimal devido à falta de virtual

    delete wa;

    return 0;
}
