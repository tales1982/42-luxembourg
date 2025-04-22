/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:30:14 by tlima-de          #+#    #+#             */
/*   Updated: 2025/04/22 13:01:03 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/AForm.hpp"
#include "../include/Bureaucrat.hpp"
#include "../include/ShrubberyCreationForm.hpp"
#include "../include/RobotomyRequestForm.hpp"
#include "../include/PresidentialPardonForm.hpp"
#include "../include/Intern.hpp"

int main() {
    Bureaucrat bureaucrat("John", 1);
    Intern intern;

    AForm *form1 = intern.makeForm("ShrubberyCreationForm", "Garden");
    AForm *form2 = intern.makeForm("RobotomyRequestForm", "Bender");
    AForm *form3 = intern.makeForm("PresidentialPardonForm", "Zaphod");

    std::cout << *form1 << std::endl;
    std::cout << *form2 << std::endl;
    std::cout << *form3 << std::endl;

    bureaucrat.signForm(*form1);
    bureaucrat.executeForm(*form1);

    bureaucrat.signForm(*form2);
    bureaucrat.executeForm(*form2);

    bureaucrat.signForm(*form3);
    bureaucrat.executeForm(*form3);

    delete form1;
    delete form2;
    delete form3;

    return 0;
}   