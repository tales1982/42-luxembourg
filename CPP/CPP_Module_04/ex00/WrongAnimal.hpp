/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:13:39 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:07:09 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

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
