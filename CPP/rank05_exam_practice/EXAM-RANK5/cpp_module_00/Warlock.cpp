/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:52:45 by tales             #+#    #+#             */
/*   Updated: 2025/06/12 20:51:17 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Warlock.hpp"

    Warlock::Warlock(const std::string& name,const std::string& title):_name(name), _title(title)
    {
        std::cout << _name << " Este parece ser outro dia entediante."<<std::endl;
    };

    
    Warlock::~Warlock()
    {
        std::cout << _name << " Meu trabalho aqui está feito!" <<std::endl;
    };

    //getters
    const std::string Warlock::getName()const{return _name;} ;
    
    const std::string Warlock::getTitle()const{return _title;} ;
    

    //setters
    void Warlock::setTitle(const std::string& newTitle){_title = newTitle;};
    
    void Warlock::introduce() const
    {
        std::cout<< _name << ": Eu sou "<< _name <<","<<_title<<std::endl;
    };