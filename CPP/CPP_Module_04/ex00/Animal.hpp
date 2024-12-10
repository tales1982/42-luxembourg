/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:19:21 by tlima-de          #+#    #+#             */
/*   Updated: 2024/12/10 15:49:36 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include<iostream>
#include<string>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"



class Animal
{
protected:
    std::string _type;
public:
    //construct
    Animal();//padrao
    Animal(std::string name);//com parametros
    Animal(const Animal &copy);//copia ex; A = B obj A recerber dados obj B
    Animal  &operator=(const Animal &src);// copia por operador 
    
    //destructor
    virtual ~Animal();
    
    //metodo adcional
    virtual void makeSound()const;
    std::string getType() const;

};




#endif