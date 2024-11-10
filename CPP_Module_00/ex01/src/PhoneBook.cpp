/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 08:07:34 by tales             #+#    #+#             */
/*   Updated: 2024/11/08 15:36:46 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PhoneBook.hpp" 
#include "../include/Contact.hpp"

PhoneBook::PhoneBook() : _contactCount(0), _oldestContactIndex(0) {
    // Inicialização dos atributos, se necessário
}

PhoneBook::~PhoneBook() {
    // Limpeza, se necessário
}


void PhoneBook::addContact(const std::string &firstName, const std::string &lastName,
                           const std::string &nickName, const std::string &phoneNumber,
                           const std::string &darkestSecret) {
    // Cria um novo contato e define seus dados
    Contact contact;
    contact.setAllInfo(firstName, lastName, nickName, phoneNumber, darkestSecret);

    // Armazena o contato no array, substituindo o mais antigo se necessário
    if (_contactCount < MAX_CONTACTS) {
        _contacts[_contactCount] = contact;
        _contactCount++;
    } else {
        _contacts[_oldestContactIndex] = contact;
        _oldestContactIndex = (_oldestContactIndex + 1) % MAX_CONTACTS; // Atualiza o índice do contato mais antigo
    }
}


