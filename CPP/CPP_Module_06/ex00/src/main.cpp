/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:56:18 by tales             #+#    #+#             */
/*   Updated: 2025/05/12 13:30:04 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>

// Códigos de cor ANSI
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << RED << "Usage: ./convert <literal>" << RESET << std::endl;
        return 1;
    }

    std::cout << CYAN << "================ SCALAR CONVERTER ================" << RESET << std::endl;
    std::cout << YELLOW << "Literal received: " << argv[1] << RESET << std::endl;
    std::cout << CYAN << "==================================================" << RESET << std::endl;

    ScalarConverter::convert(argv[1]);

    std::cout << CYAN << "==================== FINISHED ====================" << RESET << std::endl;
    return 0;
}
