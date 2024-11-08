/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 07:25:22 by tales             #+#    #+#             */
/*   Updated: 2024/11/08 08:34:25 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"

int main() {
    Contact contact;
    contact.setFirstName("Alice");
    contact.setLastName("Smith");
    contact.setNickName("Al");
    contact.setPhoneNumber("123-456-7890");
    contact.setDarkestSecret("Likes pineapple on pizza");

    // Imprime todas as informações do contato
    std::cout << contact.getAllInfo() << std::endl;

    return 0;
}