/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 06:55:52 by tales             #+#    #+#             */
/*   Updated: 2024/11/08 08:33:58 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Contact.hpp"

Contact::Contact() {
    // Inicialização, se necessário
}

// Destrutor
Contact::~Contact() {
    // Limpeza, se necessário
}


void    Contact::setFirstName(std::string firstName)
{
    _firstName = firstName;
}
void    Contact::setLastName(std::string lastName)
{
    _lastName = lastName;
}
void    Contact::setNickName(std::string nickName)
{
    _nickName = nickName;
}
void    Contact::setPhoneNumber(std::string phoneNumber)
{
    _phoneNumber = phoneNumber;
}
void    Contact::setDarkestSecret(std::string darkestSecret)
{
    _darkestSecret = darkestSecret;
}

std::string Contact::getFirstName()
{
    return _firstName;
}
std::string Contact::getLastName()
{
    return _lastName;
}

std::string Contact::getNickName()
{
    return _nickName;
}
std::string Contact::getPhoneNumber()
{
    return _phoneNumber;
}

std::string Contact::getDarkestSecret()
{
    return _darkestSecret;
}

// Implementação do método para retornar todos os dados como uma única string
std::string Contact::getAllInfo() const {
    return "First Name: " + _firstName + "\n" +
           "Last Name: " + _lastName + "\n" +
           "Nickname: " + _nickName + "\n" +
           "Phone Number: " + _phoneNumber + "\n" +
           "Darkest Secret: " + _darkestSecret;
}
