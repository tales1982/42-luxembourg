/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 08:01:25 by tales             #+#    #+#             */
/*   Updated: 2024/11/08 12:42:58 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#include <iostream>

#define MAX_CONTACTS 8

class PhoneBook {
public:
    PhoneBook();
    ~PhoneBook();

    void addContact(const std::string &firstName, const std::string &lastName,
                    const std::string &nickName, const std::string &phoneNumber,
                    const std::string &darkestSecret);
    void printContacts() const;
    void    printMenu();

private:
    Contact _contacts[MAX_CONTACTS]; // Array para armazenar contatos
    int _contactCount;                // Contador de contatos atuais
    int _oldestContactIndex;          // Índice do contato mais antigo
};

#endif
