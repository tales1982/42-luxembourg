/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:30:14 by tlima-de          #+#    #+#             */
/*   Updated: 2025/04/22 13:52:42 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/AForm.hpp"
#include "../include/Bureaucrat.hpp"
#include "../include/ShrubberyCreationForm.hpp"
#include "../include/RobotomyRequestForm.hpp"
#include "../include/PresidentialPardonForm.hpp"
#include "../include/Intern.hpp"


int main() {
    Bureaucrat bob("Bob", 1);
    Intern intern;

    std::cout << CYAN << "\n========= SHURBBERY TEST =========" << RESET << std::endl;
    AForm *form1 = intern.makeForm("shrubbery creation", "home");
    if (form1) {
        std::cout << *form1 << std::endl;
        bob.signForm(*form1);
        bob.executeForm(*form1);
        delete form1;
    }

    std::cout << CYAN << "\n========= ROBOTOMY TEST =========" << RESET << std::endl;
    AForm *form2 = intern.makeForm("robotomy request", "Bender");
    if (form2) {
        std::cout << *form2 << std::endl;
        bob.signForm(*form2);
        bob.executeForm(*form2);
        delete form2;
    }

    std::cout << CYAN << "\n========= PRESIDENTIAL PARDON TEST =========" << RESET << std::endl;
    AForm *form3 = intern.makeForm("presidential pardon", "Suelen");
    if (form3) {
        std::cout << *form3 << std::endl;
        bob.signForm(*form3);
        bob.executeForm(*form3);
        delete form3;
    }

    std::cout << CYAN << "\n========= ERRO: RUN UNSIGNED FORM =========" << RESET << std::endl;
    AForm *form4 = new ShrubberyCreationForm("forest");
    std::cout << *form4 << std::endl;
    Bureaucrat john("John", 1);
    john.executeForm(*form4);
    delete form4;

    return 0;
}