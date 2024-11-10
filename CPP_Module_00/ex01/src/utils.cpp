/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:13:52 by tales             #+#    #+#             */
/*   Updated: 2024/11/10 15:43:51 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/PhoneBook.hpp" 
#include "../include/Contact.hpp"

void PhoneBook::printMenu() {
    std::cout << "=======================================" << std::endl;
    std::cout << "|     Welcome to the PhoneBook!       |" << std::endl;
    std::cout << "|     Choose an option:               |" << std::endl;

    // Cor verde para "ADD"
    std::cout << "|     \033[32mADD\033[0m: a new contact              |" << std::endl;

    // Cor amarela para "SEARCH"
    std::cout << "|     \033[33mSEARCH\033[0m: Print all contacts      |" << std::endl;

    // Cor vermelha para "EXIT"
    std::cout << "|     \033[31mEXIT\033[0m: to exit                   |" << std::endl;

    std::cout << "=======================================" << std::endl;
}

void PhoneBook::printContacts() const {
    // Imprime todos os contatos armazenados
    for (int i = 0; i < _contactCount; i++) {
        std::cout << "Contact " << i + 1 << ":\n";
        std::cout << _contacts[i].getAllInfo() << std::endl;
        std::cout << std::endl;
    }
}

/*void PhoneBook::searchContact( _id_t ) const {

}*/