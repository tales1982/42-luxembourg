/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:55:13 by tales             #+#    #+#             */
/*   Updated: 2025/06/11 21:59:46 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <iostream>
#include <string>

class Warlock
{
private:
    std::string _name;
    std::string _title;
public:
    Warlock(const std::string& name, const std::string& title);
    ~Warlock();

    std::string getName()const;
    std::string getTitle()const;
    
    void setTitle(const std::string newTitle);
    void introduce() const;
};





#endif