/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:02:23 by tales             #+#    #+#             */
/*   Updated: 2025/06/09 19:16:41 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>

// ANSI Colors
#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BOLD    "\033[1m"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./PmergeMe <sequence of positive integers>" << std::endl;
        return 1;
    }

    try {
        std::vector<std::string> args(argv + 1, argv + argc);
        PmergeMe sorter(args);
        sorter.run();
    } catch (std::exception &e) {
        std::cerr << YELLOW << BOLD << "Error: " << e.what() << RESET << std::endl;
        return 1;
    }

    return 0;
}
