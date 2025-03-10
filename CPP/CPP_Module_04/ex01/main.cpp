/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:19:14 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:09:16 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int	main(void)
{
	Animal *animals[4];

	for (int i = 0; i < 2; i++)
		animals[i] = new Dog();
	for (int i = 2; i < 4; i++)
		animals[i] = new Cat();

	for (int i = 0; i < 4; i++)
		animals[i]->makeSound();

	for (int i = 0; i < 4; i++)
		delete animals[i];

	const WrongAnimal *wrongMeta = new WrongAnimal();
	const WrongAnimal *wrongCat = new WrongCat();
	std::cout << wrongCat->getType() << " " << std::endl;
	wrongMeta->makeSound();
	wrongCat->makeSound();
	delete wrongMeta;
	delete wrongCat;

	return (0);
}