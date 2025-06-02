/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:46:48 by tlima-de          #+#    #+#             */
/*   Updated: 2025/05/27 10:46:51 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Span.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

#define RESET       "\033[0m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define BOLD        "\033[1m"

void printTestTitle(const std::string& title) {
    std::cout << BOLD << CYAN << "\n=== " << title << " ===\n" << RESET;
}

void testBasicSpan() {
    printTestTitle("Basic test with 5 numbers");

    Span sp(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);

    std::cout << GREEN << "Shortest span: " << RESET << sp.shortestSpan() << std::endl;
    std::cout << GREEN << "Longest span : " << RESET << sp.longestSpan() << std::endl;
}

void testExceptionEmpty() {
    printTestTitle("Exception: empty vector");

    try {
        Span sp(5);
        std::cout << sp.shortestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << RED << "Caught error: " << e.what() << RESET << std::endl;
    }
}

void testExceptionOneElement() {
    printTestTitle("Exception: only one number");

    try {
        Span sp(5);
        sp.addNumber(42);
        std::cout << sp.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cout << RED << "Caught error: " << e.what() << RESET << std::endl;
    }
}

void testLargeSpan() {
    printTestTitle("Test with 10,000 random numbers");

    Span sp(10000);
    std::srand(std::time(0));

    for (int i = 0; i < 10000; ++i)
        sp.addNumber(std::rand());

    std::cout << YELLOW << "Shortest span: " << RESET << sp.shortestSpan() << std::endl;
    std::cout << YELLOW << "Longest span : " << RESET << sp.longestSpan() << std::endl;
}

void testDuplicateNumbers() {
    printTestTitle("Test with duplicate numbers");

    Span sp(4);
    sp.addNumber(5);
    sp.addNumber(5);
    sp.addNumber(5);
    sp.addNumber(5);

    std::cout << GREEN << "Shortest span: " << RESET << sp.shortestSpan() << std::endl;
    std::cout << GREEN << "Longest span : " << RESET << sp.longestSpan() << std::endl;
}

int main() {
    testBasicSpan();
    testExceptionEmpty();
    testExceptionOneElement();
    testDuplicateNumbers();
    testLargeSpan();

    return 0;
}
