/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:25:48 by tlima-de          #+#    #+#             */
/*   Updated: 2025/05/26 16:25:51 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "easyfind.hpp"

// ANSI colors
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

int main() {
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    std::cout << YELLOW << "Testing search for 3..." << RESET << std::endl;
    try {
        std::vector<int>::iterator it = easyfind(v, 3);
        std::cout << GREEN << "Found: " << *it << RESET << std::endl;
    } catch (const std::exception& e) {
        std::cout << RED << "Not found: " << e.what() << RESET << std::endl;
    }

    std::cout << YELLOW << "Testing search for 10..." << RESET << std::endl;
    try {
        std::vector<int>::iterator it = easyfind(v, 10);
        std::cout << GREEN << "Found: " << *it << RESET << std::endl;
    } catch (const std::exception& e) {
        std::cout << RED << "Not found: " << e.what() << RESET << std::endl;
    }

    // Testando o primeiro elemento
    std::cout << YELLOW << "Testing search for 1 (first element)..." << RESET << std::endl;
    try {
        std::vector<int>::iterator it = easyfind(v, 1);
        std::cout << GREEN << "Found: " << *it << RESET << std::endl;
    } catch (const std::exception& e) {
        std::cout << RED << "Not found: " << e.what() << RESET << std::endl;
    }

    // Testando o último elemento
    std::cout << YELLOW << "Testing search for 5 (last element)..." << RESET << std::endl;
    try {
        std::vector<int>::iterator it = easyfind(v, 5);
        std::cout << GREEN << "Found: " << *it << RESET << std::endl;
    } catch (const std::exception& e) {
        std::cout << RED << "Not found: " << e.what() << RESET << std::endl;
    }

    // Testando em um vetor vazio
    std::vector<int> empty;
    std::cout << YELLOW << "Testing search in an empty vector..." << RESET << std::endl;
    try {
        std::vector<int>::iterator it = easyfind(empty, 1);
        std::cout << GREEN << "Found: " << *it << RESET << std::endl;
    } catch (const std::exception& e) {
        std::cout << RED << "Not found: " << e.what() << RESET << std::endl;
    }

    return 0;
}
