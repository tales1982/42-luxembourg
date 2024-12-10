/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:52:32 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/10 19:37:47 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal
{
private:
    // Private Members
public:
    WrongCat();                               // padrao
    WrongCat(std::string name);               // com parametros
    WrongCat(const WrongCat &copy);           // copia ex; A = B obj A recerber dados obj B
    WrongCat &operator=(const WrongCat &src); // copia por operador

    // destructor
    ~WrongCat();
    void makeSound() const;
};

#endif