/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:27:38 by tales             #+#    #+#             */
/*   Updated: 2025/06/09 18:32:43 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define RESET   "\033[0m"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << RED << "Usage: ./RPN \"expression in RPN format\"" << RESET << std::endl;
        return 1;
    }

    try {
        int result = RPN::evaluate(argv[1]);
        std::cout << GREEN << result << RESET << std::endl;
    } catch (const std::exception& e) {
        std::cerr << RED << e.what() << RESET << std::endl;
        return 1;
    }

    return 0;
}
