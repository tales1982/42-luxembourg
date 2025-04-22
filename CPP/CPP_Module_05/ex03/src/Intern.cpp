/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:23:20 by tlima-de          #+#    #+#             */
/*   Updated: 2025/04/22 13:28:31 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/Intern.hpp"
#include "../include/ShrubberyCreationForm.hpp"
#include "../include/RobotomyRequestForm.hpp"
#include "../include/PresidentialPardonForm.hpp"



Intern::Intern() {}

Intern::Intern(const Intern &other) { *this = other; }

Intern &Intern::operator=(const Intern &other) {
    (void)other;
    return *this;
}

Intern::Intern() {}

static AForm* createShrubbery(const std::string& target) {
    return new ShrubberyCreationForm(target);
}

static AForm* createRobotomy(const std::string& target) {
    return new RobotomyRequestForm(target);
}

static AForm* createPardon(const std::string& target) {
    return new PresidentialPardonForm(target);
}




AForm *Intern::makeForm(const std::string &formName, const std::string &target) {
    typedef AForm* (*FormCreator)(const std::string&);

    struct FormOption {
        const char *name;
        FormCreator creator;
    };

    FormOption options[] = {
        { "shrubbery creation", createShrubbery },
        { "robotomy request", createRobotomy },
        { "presidential pardon", createPardon }
    };

    for (int i = 0; i < 3; ++i) {
        if (formName == options[i].name) {
            std::cout << "Intern creates " << options[i].name << std::endl;
            return options[i].creator(target);
        }
    }

    std::cout << "Intern cannot create form of type \"" << formName << "\"" << std::endl;
    return NULL;
}
