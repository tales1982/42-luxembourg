#include "../include/Bureaucrat.hpp"

int main() {

	try {
		std::cout  << "================================"  << std::endl;
		Bureaucrat a("Alice", 2);
		std::cout << GREEN << a << RESET << std::endl;
		
		a.incrementGrade(); // de 2 para 1
		std::cout << GREEN << a << RESET << std::endl;
		a.incrementGrade(); // erro (vai para 0)
		std::cout  << "================================"  << std::endl;
	} catch (std::exception& e) {
		std::cerr << RED << "Erro: " << e.what() << RESET << std::endl;
	}


	try {
		std::cout  << "================================"  << std::endl;
		Bureaucrat b("Bob", 149);
		std::cout << GREEN << b << RESET << std::endl;
		
		b.decrementGrade(); 
		std::cout << GREEN << b << RESET << std::endl;
		b.decrementGrade(); 
		std::cout << GREEN << b << RESET << std::endl;
		//a.incrementGrade(); // erro (vai para 0)
		std::cout  << "================================"  << std::endl;
	} catch (std::exception& e) {
		std::cerr << RED << "Erro: " << e.what() << RESET << std::endl;
	}


	std::cout  << "================================"  << std::endl;
	std::cout  << "========== test Copy ==========="  << std::endl;

	// Teste de cópia
	Bureaucrat c("Carol", 100);
	Bureaucrat d = c; // Construtor de cópia
	std::cout << YELLOW << d << RESET << std::endl;

	// Teste de atribuição
	Bureaucrat e;
	e = c;
	std::cout << YELLOW << e << RESET << std::endl;
	std::cout  << "================================"  << std::endl;
	return 0;
}
