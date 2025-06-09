/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:51:14 by tales             #+#    #+#             */
/*   Updated: 2025/06/09 18:51:16 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

// Definições de cores ANSI para destaque
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << RED << BOLD << "Error: could not open file." << RESET << std::endl;
        return 1;
    }
    try {
        BitcoinExchange btc("data.csv");
        std::ifstream input(argv[1]);
        if (!input) {
            std::cerr << RED << BOLD << "Error: could not open file." << RESET << std::endl;
            return 1;
        }
        std::string line;
        std::getline(input, line); // Pular o cabeçalho
        while (std::getline(input, line)) {
            if (line.empty()) continue;

            size_t pipePos = line.find('|');
            if (pipePos == std::string::npos) {
                std::cerr << YELLOW << BOLD << "Error: bad input => " << RESET 
                          << CYAN << line << RESET << std::endl;
                continue;
            }

            std::string date = line.substr(0, pipePos);
            std::string valueStr = line.substr(pipePos + 1);

            // Limpar espaços
            date.erase(date.find_last_not_of(" \t")+1);
            date.erase(0, date.find_first_not_of(" \t"));
            valueStr.erase(valueStr.find_last_not_of(" \t")+1);
            valueStr.erase(0, valueStr.find_first_not_of(" \t"));

            // Validar data
            if (!BitcoinExchange::isValidDate(date)) {
                std::cerr << YELLOW << BOLD << "Error: bad input => " << RESET 
                          << CYAN << line << RESET << std::endl;
                continue;
            }

            // Validar valor
            double value;
            std::istringstream iss(valueStr);
            iss >> value;
            if (iss.fail() || !iss.eof()) {
                std::cerr << YELLOW << BOLD << "Error: bad input => " << RESET 
                          << CYAN << line << RESET << std::endl;
                continue;
            }
            if (value < 0) {
                std::cerr << RED << BOLD << "Error: not a positive number." << RESET << std::endl;
                continue;
            }
            if (value > 1000) {
                std::cerr << RED << BOLD << "Error: too large a number." << RESET << std::endl;
                continue;
            }

            // Buscar taxa de câmbio e calcular resultado
            try {
                float rate = btc.getExchangeRate(date);
                double result = value * rate;
                std::cout << GREEN << BOLD << date << RESET
                          << CYAN << " => " << RESET
                          << YELLOW << value << RESET
                          << " = "
                          << BOLD << result << RESET << std::endl;
            } catch (const std::exception &e) {
                std::cerr << RED << BOLD << "Error: " << RESET 
                          << YELLOW << e.what() << RESET << std::endl;
            }
        }
    } catch (std::exception& e) {
        std::cerr << RED << e.what() << RESET << std::endl;
        return 1;
    }
    return 0;
}
