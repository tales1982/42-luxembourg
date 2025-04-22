/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:30:08 by tlima-de          #+#    #+#             */
/*   Updated: 2025/04/22 13:20:49 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/AForm.hpp"
#include "../include/Bureaucrat.hpp"


AForm::AForm()
    : _name("DefaultForm"), _isSigned(false),
      _gradeToSign(150), _gradeToExecute(150),
      target("default_target") {}

AForm::AForm(const std::string &name, int gradeToSign, int gradeToExecute, const std::string &target)
    : _name(name), _isSigned(false),
      _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute),
      target(target) {
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw GradeTooHighException();
    if (gradeToSign > 150 || gradeToExecute > 150)
        throw GradeTooLowException();
}

AForm::AForm(const AForm &other)
    : _name(other._name),
      _isSigned(other._isSigned),
      _gradeToSign(other._gradeToSign),
      _gradeToExecute(other._gradeToExecute),
      target(other.target) {}


AForm& AForm::operator=(const AForm &other) {
    if (this != &other) {
        _isSigned = other._isSigned;
    }
    return *this;
}

AForm::~AForm() {}


// Getters
std::string AForm::getName() const {
    return _name;
}

bool AForm::isSigned() const {
    return _isSigned;
}

int AForm::getGradeToSign() const {
    return _gradeToSign;
}

int AForm::getGradeToExecute() const {
    return _gradeToExecute;
}

std::string AForm::getTarget() const {
    return target;
}


// Método para assinar
void AForm::beSigned(const Bureaucrat &bureaucrat) {
    if (bureaucrat.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    _isSigned = true;
}


// Exceções
const char* AForm::GradeTooHighException::what() const throw() {
    return "Grade is too HIGH!";
}

const char* AForm::GradeTooLowException::what() const throw() {
    return "Grade is too LOW!";
}

// Sobrecarga do operador <<
std::ostream& operator<<(std::ostream& out, const AForm& form) {
    out << "AForm \"" << form.getName() << "\" ";

    if (form.isSigned())
        out << GREEN << "is signed" << RESET;
    else
        out << RED << "is NOT signed" << RESET;

    out << ", required grade to sign: " << form.getGradeToSign()
        << ", grade to execute: " << form.getGradeToExecute()
        << ", target: " << form.getTarget();

    return out;
}
