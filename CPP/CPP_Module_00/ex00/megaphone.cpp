/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:45:43 by tlima-de          #+#    #+#             */
/*   Updated: 2024/11/05 13:16:17 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <cctype> // For toupper


int main(int argc, char const **argv)
{
    int arg = 1;

    while (arg < argc)
    {
        int i = 0;
        while (argv[arg][i] != '\0')
        {
            std:: cout << static_cast<char>(std::toupper(argv[arg][i]));
            i++;
        }
        std:: cout << " ";
        arg++;
    }

    std:: cout << "\n";

    return 0;
}
