/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 09:45:02 by tales             #+#    #+#             */
/*   Updated: 2025/06/15 09:58:08 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

class ATarget;

class ASpell
{
    protected:
        std::string _name;
        std::string _effects;
public:
    ASpell(const std::string& name, const std::string& effects);
    virtual ~ASpell();

    //getters
    const std::string getName()const;
    const std::string getEffects()const;

    virtual ASpell* clone()const = 0;
    void launch(const ATarget &src) const;
};
