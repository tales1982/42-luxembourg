/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:29:45 by tlima-de          #+#    #+#             */
/*   Updated: 2025/04/07 18:34:59 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

// Cores ANSI como variáveis
const std::string RED     = "\033[31m";
const std::string GREEN   = "\033[32m";
const std::string YELLOW  = "\033[33m";
const std::string BLUE    = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN    = "\033[36m";
const std::string RESET   = "\033[0m";

#include <iostream>
#include <string>
#include <stdexcept>
#include"Bureaucrat.hpp"

class Form{
    private:
    const std::string _name;
    bool _isSigned;
    const int _gradeToSign;
    const int _gradeToExecute;

    public:
    	// Canonical Orthodox Form
	Form();                                      // Construtor padrão
	Form(const std::string& name, int grade);    // Construtor com parâmetros
	Form(const Form& other);               // Construtor de cópia
	Form& operator=(const Form& other);    // Operador de atribuição
	~Form();    

 
    std::string getName() const;
    bool isSigned() const;
    int getGradeToSign() const;
    int getGradeToExecute() const;

    void beSigned(const Bureaucrat& b);

    class GradeTooHighException : public std::exception {
        public:
            const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
        public:
            const char* what() const throw();
    };
}

// Sobrecarga do operador <<
std::ostream& operator<<(std::ostream& os, const Form& form);

#endif