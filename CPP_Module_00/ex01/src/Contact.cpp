/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 06:55:52 by tales             #+#    #+#             */
/*   Updated: 2024/11/10 17:15:50 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Contact.hpp"

Contact::Contact() {
    // Inicialização, se necessário
}

Contact::~Contact() {
    // Limpeza, se necessário
}

void Contact::setAllInfo(const std::string &firstName, const std::string &lastName,
                         const std::string &nickName, const std::string &phoneNumber,
                         const std::string &darkestSecret) {
    _firstName = firstName;
    _lastName = lastName;
    _nickName = nickName;
    _phoneNumber = phoneNumber;
    _darkestSecret = darkestSecret;
}

std::string Contact::getAllInfo() const {
    return "First Name: " + _firstName + "\n" +
           "Last Name: " + _lastName + "\n" +
           "Nickname: " + _nickName + "\n" +
           "Phone Number: " + _phoneNumber + "\n" +
           "Darkest Secret: " + _darkestSecret;
}