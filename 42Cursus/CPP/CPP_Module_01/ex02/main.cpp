/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:57:37 by tales             #+#    #+#             */
/*   Updated: 2024/12/01 11:19:01 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>

int main()
{
    std::string name = "HI THIS IS BRAIN";
    std::string *namePTR = &name; // Ponteiro que aponta para 'name'
    std::string &nameREF = name;  // Referência para 'name'

    std::cout << "The memory address of the string variable: " << &name << std::endl;
    std::cout << "The memory address held by stringPTR: " << namePTR << std::endl;
    std::cout << "The memory address held by stringREF: " << &nameREF << std::endl;
    std::cout << std::endl;
    std::cout << "The value of the string variable: " << name << std::endl;
    std::cout << "The value pointed to by stringPTR: " << *namePTR << std::endl;
    std::cout << "The value pointed to by stringREF: " << nameREF << std::endl;

    return (0);
}