/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:27:01 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:36:14 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

# include "WrongAnimal.hpp"

// Classe derivada WrongCat
class WrongCat : public WrongAnimal
{
public:
    // Construtor
    WrongCat();

    // Destrutor
    ~WrongCat();
};

#endif
