#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <stdexcept>

// Cores ANSI como variáveis
const std::string RED     = "\033[31m";
const std::string GREEN   = "\033[32m";
const std::string YELLOW  = "\033[33m";
const std::string BLUE    = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN    = "\033[36m";
const std::string RESET   = "\033[0m";

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
