/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 09:02:31 by tales             #+#    #+#             */
/*   Updated: 2025/06/15 11:29:30 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Warlock.hpp"

Warlock::Warlock(const std::string &name, const std::string &title) : _name(name), _title(title)
{
    std::cout << _name << ": This looks like another boring day." << std::endl;
};

Warlock::~Warlock()
{
    std::cout << getName() << ": My job here is done!" << std::endl;
}

const std::string Warlock::getName() const
{
    return _name;
};
const std::string Warlock::getTitle() const
{
    return _title;
};

void Warlock::setTitle(const std::string &newTitle)
{
    _title = newTitle;
};

void Warlock::introduce() const
{
    std::cout << _name << ": I am " << _name << ", " << _title << "!" << std::endl;
};

void Warlock::learnSpell(ASpell *spell)
{
    if (spell)
        spells[spell->getName()] = spell->clone();
}

void Warlock::forgetSpell(std::string name)
{
    std::map<std::string, ASpell *>::iterator it = spells.find(name);
    if (it != spells.end())
    {
        delete it->second;
        spells.erase(it);
    }
}

void Warlock::launchSpell(std::string name, const ATarget &target)
{
    ASpell *spell = spells[name];
    if (spell)
        spell->launch(target);
}