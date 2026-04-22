/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 07:25:22 by tales             #+#    #+#             */
/*   Updated: 2024/11/12 15:14:54 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include "Contact.hpp"
#include "PhoneBook.hpp"
#include "iomanip"

int main()
{
    PhoneBook phoneBook;
    std::string option;

    do
    {
        phoneBook.printMenu();

        std::cout << "Enter a command (ADD, SEARCH, EXIT): ";
        std::cin >> option; // Usa std::cin para ler uma palavra

        if (option == "ADD")
        {
            std::string firstName;
            std::string lastName;
            std::string nickName;
            std::string phoneNumber;
            std::string darkestSecret;

            std::cin.ignore(); // Limpa o buffer antes de ler as linhas completas

            std::cout << "First Name: ";
            std::getline(std::cin, firstName);
            std::cout << "Last Name: ";
            std::getline(std::cin, lastName);
            std::cout << "Nick Name: ";
            std::getline(std::cin, nickName);
            std::cout << "Phone Number: ";
            std::getline(std::cin, phoneNumber);
            std::cout << "Darkest Secret: ";
            std::getline(std::cin, darkestSecret);

            if (firstName == "" || lastName == "" || nickName == "" || phoneNumber == "" || darkestSecret.size() == 0)
            {
                std::cout << "\033[31mERROR: All fields must be filled in. Missing information in one or more fields:"
                          << (firstName == "" ? "First Name " : "")
                          << (lastName == "" ? "Last Name " : "")
                          << (nickName == "" ? "Nick Name " : "")
                          << (phoneNumber == "" ? "Phone Number " : "")
                          << (darkestSecret.size() == 0 ? "Darkest Secret" : "")
                          << ".\033[0m" << std::endl;
                return (1);
            }

            else
            {
                phoneBook.addContact(firstName, lastName, nickName, phoneNumber, darkestSecret);
                std::cout << "\033[32mContact added successfully\033[0m"<< std::endl;
            }
                
        }
        else if (option == "SEARCH")
        {
            if (phoneBook.isEmpty())
            {
                std::cout << "\033[31mDirectory is empty\033[0m" << std::endl;
            }
            else
            {
                phoneBook.printContacts();
            }
        }

        else if (option == "EXIT")
        {
            break;
        }
        else
        {
            std::cout << "Invalid option" << std::endl;
        }
    } while (option != "EXIT");

    return 0;
}
