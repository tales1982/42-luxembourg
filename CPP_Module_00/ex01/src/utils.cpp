/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:13:52 by tales             #+#    #+#             */
/*   Updated: 2024/11/10 17:38:34 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PhoneBook.hpp"
#include "../include/Contact.hpp"

void PhoneBook::printMenu()
{
    std::cout << "\033[34m=======================================\033[0m" << std::endl;
    std::cout << "\033[34m|     Welcome to the PhoneBook!       |\033[0m" << std::endl;
    std::cout << "\033[34m|     Choose an option:               |\033[0m" << std::endl;

    // Cor verde para "ADD"
    std::cout << "\033[34m|     \033[32mADD\033[0m: a new contact             \033[34m |\033[0m" << std::endl;

    // Cor amarela para "SEARCH"
    std::cout << "\033[34m|     \033[33mSEARCH\033[0m: Print all contacts      \033[34m|\033[0m" << std::endl;

    // Cor vermelha para "EXIT"
    std::cout << "\033[34m|     \033[31mEXIT\033[0m: to exit                   \033[34m|\033[0m" << std::endl;

    std::cout << "\033[34m=======================================\033[0m" << std::endl;
}

#include <iomanip>

// Função auxiliar para formatar e truncar texto para 10 caracteres com alinhamento à direita
std::string formatColumn(const std::string &text)
{
    if (text.length() > 10)
    {
        return text.substr(0, 9) + ".";
    }
    return std::string(10 - text.length(), ' ') + text;
}

void PhoneBook::printContacts() const
{
    std::cout << "\033[34m=============================================\033[0m" << std::endl;
    std::cout << "\033[34m|\033[0m    Index \033[34m|\033[0mFirst Name\033[34m|\033[0m Last Name| Nickname\033[0m \033[34m|\033[0m" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    for (int i = 0; i < _contactCount; i++)
    {
        std::cout << "\033[34m|\033[0m" << std::setw(10) << i + 1 << "\033[34m|\033[0m"
                  << formatColumn(_contacts[i].getFirstName()) << "\033[34m|\033[0m"
                  << formatColumn(_contacts[i].getLastName()) << "\033[34m|\033[0m"
                  << formatColumn(_contacts[i].getNickName()) << "\033[34m|\033[0m" << std::endl;
    }
    std::cout << "\033[34m=============================================\033[0m" << std::endl;
    int index;
    std::cout << "Enter the index of the contact to display details: ";
    std::cin >> index;

    if (std::cin.fail() || index < 1 || index > _contactCount)
    {
        std::cin.clear();                                                   // Clear the error flag on cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining input
        std::cout << "Invalid index. Please enter a valid number." << std::endl;
    }
    else
    {
        std::cout << "Contact details:\n"
                  << _contacts[index - 1].getAllInfo() << std::endl;
    }
}
