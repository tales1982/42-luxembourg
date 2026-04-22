/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:52:52 by tales             #+#    #+#             */
/*   Updated: 2025/06/12 20:53:07 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

class Warlock
{
private:
    std::string _name;
    std::string _title;
public:
    Warlock(const std::string& name,const std::string& title);
    ~Warlock();

    //getters
    const std::string getName()const ;
    const std::string getTitle()const ;
    

    //setters
    void setTitle(const std::string& newTitle);
    
    void introduce() const;
};

