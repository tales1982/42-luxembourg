#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

BitcoinExchange::BitcoinExchange(const std::string& databaseFile) {
    loadDatabase(databaseFile);
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::string& databaseFile) {
    std::ifstream file(databaseFile.c_str());
    if (!file)
        throw std::runtime_error("Error: could not open database file.");
    std::string line;
    // Pula o cabeçalho se houver
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date, rateStr;
        if (std::getline(ss, date, ',') && std::getline(ss, rateStr)) {
            std::istringstream iss(rateStr);
            float rate = 0.0f;
            iss >> rate;
            _database[date] = rate;
        }
    }
}

float BitcoinExchange::getExchangeRate(const std::string& date) const {
    std::map<std::string, float>::const_iterator it = _database.lower_bound(date);
    if (it != _database.end() && it->first == date) {
        return it->second;
    }
    if (it == _database.begin()) {
        // Não existe data anterior, erro!
        throw std::runtime_error("Error: no earlier date in database.");
    }
    --it; // Pega a data anterior mais próxima
    return it->second;
}

bool BitcoinExchange::isValidDate(const std::string& date) {
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    // Simples: checa se as partes são números
    for (size_t i = 0; i < date.size(); ++i) {
        if (i == 4 || i == 7)
            continue;
        if (!isdigit(date[i]))
            return false;
    }
   
    return true;
}
