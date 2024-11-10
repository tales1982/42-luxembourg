/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 07:25:22 by tales             #+#    #+#             */
/*   Updated: 2024/11/08 15:35:57 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"
#include <iostream>
#include <string>

int main() {
    PhoneBook phoneBook;
    std::string option;

    do { 
        phoneBook.printMenu();  // Exibe o menu

        std::cout << "Enter a command (ADD, SEARCH, EXIT): ";
        std::cin >> option;  // Lê a opção antes de verificar

        if(option == "ADD") {
            std::string firstName;
            std::string lastName;
            std::string nickName;
            std::string phoneNumber;
            std::string darkestSecret;

            std::cout << "First Name: ";
            std::cin >> firstName;
            std::cout << "Last Name: ";
            std::cin >> lastName;
            std::cout << "Nick Name: ";
            std::cin >> nickName;
            std::cout << "Phone Number: ";
            std::cin >> phoneNumber;
            std::cout << "Darkest Secret: ";
            std::cin >> darkestSecret;

            phoneBook.addContact(firstName, lastName, nickName, phoneNumber, darkestSecret);
        }
        else if(option == "SEARCH") {
            phoneBook.printContacts();
        }
        else if(option == "EXIT") {
            break; 
        }
        else {
            std::cout << "Invalid option" << std::endl;
        }
    } while (option != "EXIT");

    return 0;
}
