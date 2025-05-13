/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:54:55 by tlima-de          #+#    #+#             */
/*   Updated: 2025/05/13 13:47:29 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// main.cpp
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "functions.hpp"


// Códigos de cor ANSI
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"


int main() {
    std::srand(std::time(0)); // Inicializa o gerador de números aleatórios

    std::cout << BLUE << "[+] Generating random instance of A, B or C...\n" << RESET;
    Base* ptr = generate();   // Gera uma instância aleatória

    std::cout << YELLOW << "[*] Identification with pointer:\n" << RESET;
    identify(ptr);            // Identifica com ponteiro

    std::cout << YELLOW << "[*] Identification with reference:\n" << RESET;
    identify(*ptr);           // Identifica com referência

    delete ptr;
    std::cout << GREEN << "[✓] Successful deleted instance.\n" << RESET;

    return 0;
}