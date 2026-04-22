/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATarget.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:02:52 by tales             #+#    #+#             */
/*   Updated: 2025/06/15 11:15:35 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

class ASpell;

class ATarget
{
protected:
    std::string _type;
public:
    ATarget(const std::string& type);
    virtual ~ATarget();

    const std::string& getType()const ;
    virtual ATarget* clone()const = 0;
    void getHitBySpell(const ASpell& src)const;
};

