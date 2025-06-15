/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 09:58:22 by tales             #+#    #+#             */
/*   Updated: 2025/06/15 10:22:38 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASpell.hpp"
#include "ATarget.hpp"

    ASpell::ASpell(const std::string& name, const std::string& effects):_name(name), _effects(effects){};
    
    ASpell::~ASpell(){};

    //getters
    const std::string ASpell::getName()const{return _name;};
    
    const std::string ASpell::getEffects()const{return _effects;};

    void ASpell::launch(const ATarget &src) const
    {
        src.getHitBySpell(*this);
    };