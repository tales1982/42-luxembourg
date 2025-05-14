/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:54:55 by tlima-de          #+#    #+#             */
/*   Updated: 2025/05/14 10:22:58 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Serializer.hpp"

// COR ANSI CODES
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

int main() {
    Data original;
    original.id = 42;
    original.name = "Tales";

    std::cout << CYAN << "============================================" << RESET << std::endl;
    std::cout << YELLOW << "Original Data address: " << &original << RESET << std::endl;
    std::cout << CYAN << "============================================" << RESET << std::endl;

    uintptr_t raw = Serializer::serialize(&original);

    std::cout << BLUE << "Serialized (uintptr_t): " << raw << RESET << std::endl;
    std::cout << CYAN << "============================================" << RESET << std::endl;

    Data* recovered = Serializer::deserialize(raw);
    std::cout << YELLOW << "Recovered Data address: " << recovered << RESET << std::endl;
    std::cout << CYAN << "============================================" << RESET << std::endl;

    if (recovered == &original)
        std::cout << GREEN << "Success: pointers match!" << RESET << std::endl;
    else
        std::cout << RED << "Failure: pointers do not match!" << RESET << std::endl;

    std::cout << BLUE << "Recovered Data ID: " << recovered->id 
              << ", Name: " << recovered->name << RESET << std::endl;

    return 0;
}
