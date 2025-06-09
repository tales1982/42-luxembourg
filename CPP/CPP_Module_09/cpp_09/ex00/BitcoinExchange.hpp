/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:50:38 by tales             #+#    #+#             */
/*   Updated: 2025/06/09 18:50:42 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>

class BitcoinExchange {
public:
    // Constrói e carrega o banco de dados CSV
    BitcoinExchange(const std::string& databaseFile);
    ~BitcoinExchange();

    // Retorna a taxa de bitcoin para uma data (ou data anterior mais próxima)
    float getExchangeRate(const std::string& date) const;

    // Verifica se uma string está no formato de data válido (YYYY-MM-DD)
    static bool isValidDate(const std::string& date);

private:
    std::map<std::string, float> _database; // data -> exchange_rate
    void loadDatabase(const std::string& databaseFile);
};

#endif
