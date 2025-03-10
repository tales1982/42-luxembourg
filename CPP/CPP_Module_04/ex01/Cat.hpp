/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:19:01 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:08:54 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class Cat : public Animal
{
  private:
	Brain *_brain;

  public:
	Cat();

	Cat(const Cat &other);

	Cat &operator=(const Cat &other);

	~Cat();

	void makeSound() const;
	Brain *getBrain() const;
};

#endif
