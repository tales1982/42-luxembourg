/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dummy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:32:32 by tales             #+#    #+#             */
/*   Updated: 2025/06/15 11:18:46 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ATarget.hpp"

class Dummy : public ATarget
{
private:
    /* data */
public:
    Dummy(/* args */);
    ~Dummy();
    
    ATarget* clone()const ;
};

