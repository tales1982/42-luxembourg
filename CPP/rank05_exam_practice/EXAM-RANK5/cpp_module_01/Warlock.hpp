/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 08:52:45 by tales             #+#    #+#             */
/*   Updated: 2025/06/15 11:25:25 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <map>

#include "ASpell.hpp"
#include "ATarget.hpp"


class Warlock
{
private:
    std::string _name;
    std::string _title;
    std::map<std::string, ASpell*> spells;

public:
    Warlock(const std::string &name, const std::string &title);
    ~Warlock();

    const std::string getName() const;
    const std::string getTitle() const;

    void setTitle(const std::string &newTitle);

    void introduce() const;

    void learnSpell(ASpell* spell);
    void forgetSpell(std::string name);
    void launchSpell(std::string name, const ATarget& target);
};