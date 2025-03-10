/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:40:24 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:14:13 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include "AAnimal.hpp"
# include "Brain.hpp"

class Cat : public AAnimal
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
