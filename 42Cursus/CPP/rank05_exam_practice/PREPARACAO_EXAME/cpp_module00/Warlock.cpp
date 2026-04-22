/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:57:48 by tales             #+#    #+#             */
/*   Updated: 2025/06/09 22:02:37 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Warlock.hpp"


    
    Warlock::Warlock(const std::string& name, const std::string& title):_name(name), _title(title){};
    
    Warlock::~Warlock()
    {
        std::cout << getName() << ": My job here is done!" << std::endl;
    }

    const std::string& Warlock::getName()const
    {
        return _name;
    }
    
    const std::string& Warlock::getTitle()const
    {
        return _title;
    }
    
    void Warlock::introduce()const
    {
        std::cout << _name << ": I am " << _name << ", " << _title << "!" << std::endl;

    }