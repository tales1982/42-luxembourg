/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:05:36 by tales             #+#    #+#             */
/*   Updated: 2024/12/02 20:25:23 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl() {
    // Construtor padrão (pode estar vazio)
}

Harl::~Harl() {
    // Destrutor padrão (pode estar vazio)
}


// Implementação dos métodos privados
void Harl::debug() {
    std::cout << "[DEBUG] I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!" << std::endl;
}

void Harl::info() {
    std::cout << "[INFO] I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger!" << std::endl;
}

void Harl::warning() {
    std::cout << "[WARNING] I think I deserve to have some extra bacon for free. I’ve been coming for years." << std::endl;
}

void Harl::error() {
    std::cout << "[ERROR] This is unacceptable! I want to speak to the manager now." << std::endl;
}

// Implementação de complain usando ponteiros para funções membro
void Harl::complain(std::string level) {
    // Define um tipo de ponteiro para funções membro
    typedef void (Harl::*HarlFunction)();

    // Array associando níveis de reclamação aos métodos correspondentes
    const std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    HarlFunction functions[] = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};

    // Verifica o nível e chama a função correspondente
    for (int i = 0; i < 4; i++) {
        if (levels[i] == level) {
            (this->*functions[i])(); // Chama a função correspondente ao nível
            return;
        }
    }

    // Caso o nível não seja encontrado
    std::cout << "[UNKNOWN] This level is not recognized." << std::endl;
}
