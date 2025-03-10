/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:19:10 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:09:10 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class Dog : public Animal
{
  private:
	Brain *_brain;

  public:
	Dog();

	Dog(const Dog &other);

	Dog &operator=(const Dog &other);

	~Dog();

	void makeSound() const;
	Brain *getBrain() const;
};

#endif
