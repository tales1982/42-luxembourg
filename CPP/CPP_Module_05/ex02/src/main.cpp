/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:30:14 by tlima-de          #+#    #+#             */
/*   Updated: 2025/04/16 11:21:15 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/AForm.hpp"
#include "../include/Bureaucrat.hpp"
#include "../include/ShrubberyCreationForm.hpp"
#include "../include/RobotomyRequestForm.hpp"
#include "../include/PresidentialPardonForm.hpp"

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main() {
    try {
        std::cout << CYAN << "==== SHRUBBERY TEST ====" << RESET << std::endl;
        Bureaucrat bob("Bob", 100);
        ShrubberyCreationForm shrub("home");

        std::cout << shrub << std::endl;
        bob.signForm(shrub);
        bob.executeForm(shrub);

        std::cout << std::endl << CYAN << "==== ROBOTOMY TEST ====" << RESET << std::endl;
        Bureaucrat rob("Rob", 40); // grade suficiente
        RobotomyRequestForm robot("Bender");

        std::cout << robot << std::endl;
        rob.signForm(robot);
        rob.executeForm(robot);  // pode falhar ou não, por chance

        std::cout << std::endl << CYAN << "==== PRESIDENTIAL PARDON TEST ====" << RESET << std::endl;
        Bureaucrat zaphod("Zaphod", 1); // grade máxima
        PresidentialPardonForm pardon("Suelen");

        std::cout << pardon << std::endl;
        zaphod.signForm(pardon);
        zaphod.executeForm(pardon);

        std::cout << std::endl << CYAN << "==== ERRO: RUN UNSIGNED FORM ====" << RESET << std::endl;
        Bureaucrat john("John", 1);
        ShrubberyCreationForm notSignedForm("forest");

        std::cout << notSignedForm << std::endl;
        john.executeForm(notSignedForm); // erro esperado

    } catch (std::exception &e) {
        std::cerr << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    return 0;
}
