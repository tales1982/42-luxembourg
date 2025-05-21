/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:46:58 by coder             #+#    #+#             */
/*   Updated: 2025/05/21 11:24:03 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include "Array.hpp"
#include <string>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"

// Function to print test titles
void printTitle(const std::string& title) {
    std::cout << BLUE << "\n===== " << title << " =====" << RESET << std::endl;
}

// Test default constructor
void testDefaultConstructor() {
    printTitle("Test: Default Constructor");
    Array<int> a;
    std::cout << CYAN << "Array<int> a;" << RESET << std::endl;
    std::cout << "Size: " << a.size() << std::endl;
    try {
        a[0] = 1; // Should throw an exception
    } catch (std::exception& e) {
        std::cout << GREEN << "[OK] Exception thrown when accessing index 0: " << e.what() << RESET << std::endl;
    }
}

// Test parameterized constructor
void testParameterizedConstructor() {
    printTitle("Test: Parameterized Constructor");
    Array<std::string> a(3);
    std::cout << CYAN << "Array<std::string> a(3);" << RESET << std::endl;
    a[0] = "42";
    a[1] = "Luxembourg";
    a[2] = "Thales";
    for (unsigned int i = 0; i < a.size(); ++i)
        std::cout << "a[" << i << "] = " << a[i] << std::endl;
    std::cout << "Size: " << a.size() << std::endl;
}

// Test copy constructor
void testCopyConstructor() {
    printTitle("Test: Copy Constructor");
    Array<double> a(2);
    a[0] = 3.14;
    a[1] = 2.718;
    Array<double> b(a); // copy
    b[1] = 1.618;
    std::cout << "a[1] = " << a[1] << " (should be 2.718)" << std::endl;
    std::cout << "b[1] = " << b[1] << " (should be 1.618)" << std::endl;
    if (a[1] != b[1])
        std::cout << GREEN << "[OK] Deep copy working!" << RESET << std::endl;
    else
        std::cout << RED << "[FAIL] Deep copy not working!" << RESET << std::endl;
}

// Test assignment operator
void testAssignmentOperator() {
    printTitle("Test: Assignment Operator");
    Array<char> a(2);
    a[0] = 'A';
    a[1] = 'B';
    Array<char> b;
    b = a;
    b[0] = 'Z';
    std::cout << "a[0] = " << a[0] << " (should be A)" << std::endl;
    std::cout << "b[0] = " << b[0] << " (should be Z)" << std::endl;
    if (a[0] != b[0])
        std::cout << GREEN << "[OK] Deep copy in assignment working!" << RESET << std::endl;
    else
        std::cout << RED << "[FAIL] Deep copy in assignment not working!" << RESET << std::endl;
}

// Test bounds checking
void testOutOfBounds() {
    printTitle("Test: Bounds Checking");
    Array<int> a(3);
    try {
        std::cout << a[3] << std::endl;
        std::cout << RED << "[FAIL] Did not throw exception for index 3!" << RESET << std::endl;
    } catch (std::exception& e) {
        std::cout << GREEN << "[OK] Exception caught for index 3: " << e.what() << RESET << std::endl;
    }
    try {
        std::cout << a[-1] << std::endl;
        std::cout << RED << "[FAIL] Did not throw exception for index -1!" << RESET << std::endl;
    } catch (std::exception& e) {
        std::cout << GREEN << "[OK] Exception caught for index -1: " << e.what() << RESET << std::endl;
    }
}

int main() {
    std::cout << MAGENTA << "===== Custom tests for Array<T> =====" << RESET << std::endl;

    testDefaultConstructor();
    testParameterizedConstructor();
    testCopyConstructor();
    testAssignmentOperator();
    testOutOfBounds();

    std::cout << MAGENTA << "\n===== END OF TESTS =====\n" << RESET;
    return 0;
}
