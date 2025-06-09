/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:27:14 by tales             #+#    #+#             */
/*   Updated: 2025/06/09 18:33:19 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// RPN.cpp
#include "RPN.hpp"
#include <stack>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cctype>

int RPN::evaluate(const std::string& expr) {
    std::stack<int> stack;
    std::stringstream ss(expr);
    std::string token;

    while (ss >> token) {
        // Se for um único dígito (de 0 a 9)
        if (token.size() == 1 && std::isdigit(token[0])) {
            stack.push(token[0] - '0');
        }
        // Se for um operador válido
        else if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack.size() < 2)
                throw std::runtime_error("Error: Not enough operands before operator '" + token + "'");

            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();

            if (token == "+") stack.push(a + b);
            else if (token == "-") stack.push(a - b);
            else if (token == "*") stack.push(a * b);
            else if (token == "/") {
                if (b == 0)
                    throw std::runtime_error("Error: Division by zero");
                stack.push(a / b);
            }
        }
        // Se for qualquer outra coisa inválida (letras, parênteses, etc.)
        else {
            throw std::runtime_error("Error: Invalid token '" + token + "'");
        }
    }

    // Após o cálculo, deve restar apenas 1 valor na pilha: o resultado
    if (stack.size() != 1)
        throw std::runtime_error("Error: Malformed expression. Final stack size is not 1.");

    return stack.top();
}
