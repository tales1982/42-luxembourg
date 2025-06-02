/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:16:34 by tlima-de          #+#    #+#             */
/*   Updated: 2025/06/02 14:16:37 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <iostream>

// ANSI colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

int main()
{
    MutantStack<int> mstack;

    std::cout << BOLD << CYAN << "[MutantStack Test]\n" << RESET;

    mstack.push(5);
    mstack.push(17);
    std::cout << GREEN << "Top: " << RESET << mstack.top() << std::endl;

    mstack.pop();
    std::cout << GREEN << "Size after pop: " << RESET << mstack.size() << std::endl;

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    std::cout << BOLD << "\n[Iterating through MutantStack]" << RESET << std::endl;
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    while (it != ite)
    {
        std::cout << YELLOW << *it << RESET << std::endl;
        ++it;
    }

    // std::stack copy (loses iteration ability)
    std::stack<int> s(mstack);
    std::cout << BOLD << "\n[Iterating through copied std::stack (LIFO)]" << RESET << std::endl;
    while (!s.empty())
    {
        std::cout << BLUE << s.top() << RESET << std::endl;
        s.pop();
    }

    std::cout << BOLD << CYAN << "\n[Test complete]" << RESET << std::endl;

    return 0;
}
