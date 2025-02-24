/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:27:04 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:39:45 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
# define CURE_HPP

# include "AMateria.hpp"

// Classe concreta Cure
class Cure : public AMateria
{
public:
    Cure();
    Cure(Cure const &other);
    Cure &operator=(Cure const &other);
    virtual ~Cure();

    // Clona a matéria
    virtual AMateria* clone() const;

    // Usa a matéria Cure
    virtual void use(ICharacter& target);
};

#endif
