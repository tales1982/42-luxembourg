/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:18:41 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:08:20 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>
# include <string>

// Definindo as macros para as cores
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define CYAN "\033[36m"
# define MAGENTA "\033[35m"
# define RESET "\033[0m"

class Animal
{
  protected:
	std::string _type;

  public:
	Animal();

	Animal(const Animal &other);

	Animal &operator=(const Animal &other);

	virtual ~Animal();

	virtual void makeSound() const;
	std::string getType() const;
};

#endif
