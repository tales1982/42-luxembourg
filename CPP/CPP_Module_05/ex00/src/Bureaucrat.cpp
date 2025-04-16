#include "../include/Bureaucrat.hpp"

// Construtor padrão
Bureaucrat::Bureaucrat() : _name("Default"), _grade(150) {}


Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name) {
	if (grade < 1)
		throw GradeTooHighException();
	if (grade > 150)
		throw GradeTooLowException();
	_grade = grade;
}


Bureaucrat::Bureaucrat(const Bureaucrat& other)
	: _name(other._name), _grade(other._grade) {}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
	if (this != &other)
		this->_grade = other._grade; 
	return *this;
}


Bureaucrat::~Bureaucrat() {}

const std::string& Bureaucrat::getName() const {
	return _name;
}

int Bureaucrat::getGrade() const {
	return _grade;
}

void Bureaucrat::incrementGrade() {
	if (_grade - 1 < 1)
		throw GradeTooHighException();
	--_grade;
}

void Bureaucrat::decrementGrade() {
	if (_grade + 1 > 150)
		throw GradeTooLowException();
	++_grade;
}

const char* Bureaucrat::GradeTooHighException::what() const throw() {
	return "Grade too high!";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
	return "Grade too low!";
}

std::ostream& operator<<(std::ostream& out, const Bureaucrat& b) {
	out << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
	return out;
}
