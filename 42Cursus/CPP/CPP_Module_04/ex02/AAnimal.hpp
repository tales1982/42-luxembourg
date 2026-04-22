/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:36:20 by tlima-de          #+#    #+#             */
/*   Updated: 2025/03/05 16:14:03 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AANIMAL_HPP
# define AANIMAL_HPP

# include <iostream>
# include <string>

// Definindo as macros para as cores
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define CYAN "\033[36m"    // Ciano
# define MAGENTA "\033[35m" // Magenta
# define RESET "\033[0m"    // Reseta a cor para o padrão

class AAnimal
{
  protected:
	std::string _type;

  public:
	AAnimal();

	AAnimal(const AAnimal &other);

	AAnimal &operator=(const AAnimal &other);

	virtual ~AAnimal();

	virtual void makeSound() const = 0;
	std::string getType() const;
};

#endif
