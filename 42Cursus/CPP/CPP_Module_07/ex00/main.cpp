/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:34:29 by coder             #+#    #+#             */
/*   Updated: 2025/05/20 10:34:32 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whatever.hpp"
#include <iostream>
#include <string>

// COR ANSI CODES
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

int main() {
	std::cout << BLUE << "[ Test with INT ]" << RESET << std::endl;
	int a = 2, b = 3;
	std::cout << CYAN << "Before swap: a = " << a << ", b = " << b << RESET << std::endl;
	::swap(a, b);
	std::cout << GREEN << "After swap : a = " << a << ", b = " << b << RESET << std::endl;
	std::cout << YELLOW << "min = " << ::min(a, b) << RESET << std::endl;
	std::cout << RED << "max = " << ::max(a, b) << RESET << std::endl;

	std::cout << "\n" << BLUE << "[ Test with DOUBLE ]" << RESET << std::endl;
	double x = 42.42, y = 21.21;
	std::cout << CYAN << "Before swap: x = " << x << ", y = " << y << RESET << std::endl;
	::swap(x, y);
	std::cout << GREEN << "After swap : x = " << x << ", y = " << y << RESET << std::endl;
	std::cout << YELLOW << "min = " << ::min(x, y) << RESET << std::endl;
	std::cout << RED << "max = " << ::max(x, y) << RESET << std::endl;

	std::cout << "\n" << BLUE << "[ Test with STRING ]" << RESET << std::endl;
	std::string s1 = "chaine1", s2 = "chaine2";
	std::cout << CYAN << "Before swap: s1 = " << s1 << ", s2 = " << s2 << RESET << std::endl;
	::swap(s1, s2);
	std::cout << GREEN << "After swap : s1 = " << s1 << ", s2 = " << s2 << RESET << std::endl;
	std::cout << YELLOW << "min = " << ::min(s1, s2) << RESET << std::endl;
	std::cout << RED << "max = " << ::max(s1, s2) << RESET << std::endl;

	return 0;
}

