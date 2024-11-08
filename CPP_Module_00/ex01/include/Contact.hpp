/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 06:55:46 by tales             #+#    #+#             */
/*   Updated: 2024/11/08 08:33:31 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

#define MAX_CONTACTS 8

class Contact
{
public:
    Contact();
    ~Contact();
    // Declaração do método setter
    void setFirstName(std::string firstName); //  Ele permite que você defina ou atualize o valor do atributo
    void setLastName(std::string lastName);
    void setNickName(std::string nickName);
    void setPhoneNumber(std::string phoneNumber);
    void setDarkestSecret(std::string darkestSecret);

    //======Declaração do método getter

    std::string getFirstName();
    std::string getLastName();
    std::string getNickName();
    std::string getPhoneNumber();
    std::string getDarkestSecret();
    // Declaração do método para retornar todos os dados como uma única string
    std::string getAllInfo() const;

private:
    std::string _firstName; // Atributo para armazenar o primeiro nome
    std::string _lastName;
    std::string _nickName;
    std::string _phoneNumber;
    std::string _darkestSecret;
};

#endif