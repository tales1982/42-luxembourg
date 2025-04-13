/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:30:14 by tlima-de          #+#    #+#             */
/*   Updated: 2025/04/13 17:17:34 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Form.hpp"
#include "../include/Bureaucrat.hpp"
#include "../include/Color.hpp"

int main()
{
    try {
        std::cout<<"=============================================================================================="<<std::endl;
        Bureaucrat bob("Bob", 20);
        Form contract("Contract 42Lux", false, 45, 30);

        std::cout << YELLOW << bob << RESET << std::endl;
        std::cout<<"______________________________________________________________________________________________"<<std::endl;
        std::cout << "|                            current status of the contract.                                 |" << std::endl;
        std::cout <<"|" <<BLUE << contract << RESET <<" |"<< std::endl;
        std::cout<<"|____________________________________________________________________________________________|"<<std::endl;

        // Tenta assinar o formulário
        contract.beSigned(bob);
        std::cout << GREEN << "Formulário assinado com sucesso!" << RESET << std::endl;

        std::cout<<"______________________________________________________________________________________________"<<std::endl;
        std::cout << "|                     current status of the contract after signing.                          |" << std::endl;
        std::cout <<"|" <<BLUE << contract << RESET <<"|"<< std::endl;
        std::cout<<"|____________________________________________________________________________________________|"<<std::endl;
        std::cout<<"=============================================================================================="<<std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << RED << "Erro: " << e.what() << RESET << std::endl;
    }
    try {

        std::cout<<"=============================================================================================="<<std::endl;
        Bureaucrat alice("Alice", 150);
        Form contratoDif("Contract 42Lux", false, 100, 50);

        std::cout << YELLOW << alice << RESET << std::endl;
        std::cout<<"_______________________________________________________________________________________________"<<std::endl;
        std::cout << "|                            current status of the contract.                                  |" << std::endl;
        std::cout <<"|" <<BLUE << contratoDif << RESET <<" |"<< std::endl;
        std::cout<<"|_____________________________________________________________________________________________|"<<std::endl;

        // Tenta assinar o formulário
        contratoDif.beSigned(alice);
        std::cout << GREEN << "Form signed successfully!!" << RESET << std::endl;

        std::cout<<"______________________________________________________________________________________________"<<std::endl;
        std::cout << "|                     current status of the contract after signing.                          |" << std::endl;
        std::cout <<"|" <<BLUE << contratoDif << RESET <<"|"<< std::endl;
        std::cout<<"|____________________________________________________________________________________________|"<<std::endl;
        std::cout<<"=============================================================================================="<<std::endl;

    }
    catch (const std::exception &e) {
        std::cerr << RED << "Error signing: " << e.what() << RESET << std::endl;
    }

    return 0;
}

