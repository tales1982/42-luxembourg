/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:29:45 by tlima-de          #+#    #+#             */
/*   Updated: 2025/04/13 15:53:52 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include <string>
#include <stdexcept>
class Bureaucrat; 
#include "Color.hpp"


class Form{
    private:
    const std::string _name;
    bool _isSigned;
    const int _gradeToSign;
    const int _gradeToExecute;

    public:
    	// Canonical Orthodox Form
	Form();                                      // Construtor padrão
	Form(const std::string &name, bool isSigned, const int gradeToSign, const int gradeToExecute);    // Construtor com parâmetros
	Form(const Form& other);               // Construtor de cópia
	Form& operator=(const Form& other);    // Operador de atribuição
	~Form();    

 
    std::string getName() const;
    bool isSigned() const;
    int getGradeToSign() const;
    int getGradeToExecute() const;

    void beSigned(const Bureaucrat &bureaucrat);

    class GradeTooHighException : public std::exception {
        public:
            const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
        public:
            const char* what() const throw();
    };
};
// Sobrecarga do operador <<
std::ostream& operator<<(std::ostream& out, const Form& form);

#endif