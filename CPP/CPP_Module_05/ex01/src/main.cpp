#include "../include/Bureaucrat.hpp"

int main() {
	try {
		Bureaucrat a("Alice", 2);
		std::cout << GREEN << a << RESET << std::endl;

		a.incrementGrade(); // de 2 para 1
		std::cout << GREEN << a << RESET << std::endl;

		a.incrementGrade(); // erro (vai para 0)
	} catch (std::exception& e) {
		std::cerr << RED << "Erro: " << e.what() << RESET << std::endl;
	}


	try {
		Bureaucrat b("Bob", 151); // erro (grade inválido)
	} catch (std::exception& e) {
		std::cerr << RED << "Erro: " << e.what() << RESET << std::endl;
	}

	// Teste de cópia
	Bureaucrat c("Carol", 100);
	Bureaucrat d = c; // Construtor de cópia
	std::cout << YELLOW << d << RESET << std::endl;

	// Teste de atribuição
	Bureaucrat e;
	e = c;
	std::cout << YELLOW << e << RESET << std::endl;

	return 0;
}
