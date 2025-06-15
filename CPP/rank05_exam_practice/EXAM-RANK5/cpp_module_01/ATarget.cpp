/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATarget.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:03:58 by tales             #+#    #+#             */
/*   Updated: 2025/06/15 10:21:47 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATarget.hpp"
#include "ASpell.hpp"

    ATarget::ATarget(const std::string& type) : _type(type){}
    
    ATarget::~ATarget(){};

    const std::string& ATarget::getType()const {return _type;};
    
    void ATarget::getHitBySpell(const ASpell& src)const
    {
        std::cout << _type << " has been " << src.getEffects() << "!" <<std::endl;
    };