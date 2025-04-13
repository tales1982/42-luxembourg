/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:29:38 by tlima-de          #+#    #+#             */
/*   Updated: 2025/04/13 15:52:13 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include "Color.hpp"
#include "Form.hpp"

class Bureaucrat {
private:
	const std::string _name;
	int _grade;

public:
	// Canonical Orthodox Form
	Bureaucrat();                                      // Construtor padrão
	Bureaucrat(const std::string& name, int grade);    // Construtor com parâmetros
	Bureaucrat(const Bureaucrat& other);               // Construtor de cópia
	Bureaucrat& operator=(const Bureaucrat& other);    // Operador de atribuição
	~Bureaucrat();                                     // Destrutor

	const std::string& getName() const;
	int getGrade() const;

	void incrementGrade();
	void decrementGrade();

	void signForm(Form& form) const; 
	

	class GradeTooHighException : public std::exception {
	public:
		const char* what() const throw();
	};

	class GradeTooLowException : public std::exception {
	public:
		const char* what() const throw();
	};
};

std::ostream& operator<<(std::ostream& out, const Bureaucrat& b);

#endif
