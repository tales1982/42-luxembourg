/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:56:18 by tales             #+#    #+#             */
/*   Updated: 2025/05/16 12:39:41 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#include <iostream>
#include <string>

// COR ANSI CODES
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

template <typename T>
void print(const T &val) {
	std::cout << GREEN << val << RESET << std::endl;
}

int main() {
	int arr[] = {1, 2, 3, 4, 5};
	std::string words[] = {"hello", "world", "!"};

	std::cout << BLUE << "[ Test with INT array ]" << RESET << std::endl;
	iter(arr, 5, print);

	std::cout << "\n" << BLUE << "[ Test with STRING array ]" << RESET << std::endl;
	iter(words, 3, print);

	return 0;
}
