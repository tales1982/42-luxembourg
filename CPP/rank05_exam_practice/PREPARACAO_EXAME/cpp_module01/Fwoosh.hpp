/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fwoosh.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:23:11 by tales             #+#    #+#             */
/*   Updated: 2025/06/15 10:29:26 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ASpell.hpp"

class Fwoosh :public ASpell
{
private:
    /* data */
public:
    Fwoosh(/* args */);
    ~Fwoosh();
    
    ASpell* clone()const ;
};

