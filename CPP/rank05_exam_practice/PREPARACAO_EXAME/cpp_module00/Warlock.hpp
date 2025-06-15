/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:56:40 by tales             #+#    #+#             */
/*   Updated: 2025/06/09 22:00:11 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <iostream>
#include <string>

class Warlock
{
private:
    std::string _name ;
    std::string _title ;
public:

    Warlock(const std::string& name, const std::string& title);
    ~Warlock();

    const std::string& getName()const;
    const std::string& getTitle()const;
    void introduce()const;
};



#endif