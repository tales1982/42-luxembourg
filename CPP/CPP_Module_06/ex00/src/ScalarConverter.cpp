/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:10:08 by tales             #+#    #+#             */
/*   Updated: 2025/05/12 13:28:53 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ScalarConverter.hpp"

// =====================================================
// 		Construtores/Destrutores
// =====================================================
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &) {}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) { return *this; }
ScalarConverter::~ScalarConverter() {}

// =====================================================
// 		Funções auxiliares de verificação
// =====================================================
bool ScalarConverter::isInt(const std::string &s)
{
    size_t i = 0;
    if (s[i] == '+' || s[i] == '-')
        i++;
    while (i < s.length() && std::isdigit(s[i]))
        i++;
    return (i == s.length());
}

bool ScalarConverter::isFloat(const std::string &s)
{
    if (s == "nanf" || s == "+inff" || s == "-inff")
        return true;
    size_t i = 0;
    if (s[i] == '+' || s[i] == '-')
        i++;
    bool dot = false, digit = false;
    while (i < s.length() && (std::isdigit(s[i]) || s[i] == '.'))
    {
        if (s[i] == '.')
            dot = true;
        else
            digit = true;
        i++;
    }
    return (dot && digit && s[i] == 'f' && i + 1 == s.length());
}

bool ScalarConverter::isDouble(const std::string &s)
{
    if (s == "nan" || s == "+inf" || s == "-inf")
        return true;
    size_t i = 0;
    if (s[i] == '+' || s[i] == '-')
        i++;
    bool dot = false, digit = false;
    while (i < s.length() && (std::isdigit(s[i]) || s[i] == '.'))
    {
        if (s[i] == '.')
            dot = true;
        else
            digit = true;
        i++;
    }
    return (dot && digit && i == s.length());
}

// =====================================================
// 		Função principal de conversão
// =====================================================
void ScalarConverter::convert(const std::string &literal)
{
    if (literal.length() == 1 && std::isprint(static_cast<unsigned char>(literal[0])))
    {
        convertFromChar(literal[0]);
    }
    else if (isInt(literal))
    {
        int i = std::atoi(literal.c_str());
        convertFromInt(i);
    }
    else if (isFloat(literal))
    {
        float f = std::strtof(literal.c_str(), NULL);
        convertFromFloat(f);
    }
    else if (isDouble(literal))
    {
        double d = std::strtod(literal.c_str(), NULL);
        convertFromDouble(d);
    }
    else
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
    }
}

// =====================================================
// 		Funções específicas de conversão
// =====================================================
void ScalarConverter::convertFromChar(char c)
{
    std::cout << "char: '" << c << "'" << std::endl;
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(c) << "f" << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(c) << std::endl;
}

void ScalarConverter::convertFromInt(int i)
{
    if (i < 0 || i > 127)
        std::cout << "char: impossible" << std::endl;
    else if (std::isprint(i))
        std::cout << "char: '" << static_cast<char>(i) << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;

    std::cout << "int: " << i << std::endl;
    std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(i) << "f" << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(i) << std::endl;
}

void ScalarConverter::convertFromFloat(float f)
{
    if (f < 0 || f > 127 || isnan(f) || isinf(f))
        std::cout << "char: impossible" << std::endl;
    else if (std::isprint(static_cast<int>(f)))
        std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;

    if (f > static_cast<float>(std::numeric_limits<int>::max()) ||
        f < static_cast<float>(std::numeric_limits<int>::min()) ||
        isnan(f))
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(f) << std::endl;

    std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(f) << std::endl;
}

void ScalarConverter::convertFromDouble(double d)
{
    if (d < 0 || d > 127 || isnan(d) || isinf(d))
        std::cout << "char: impossible" << std::endl;
    else if (std::isprint(static_cast<int>(d)))
        std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;

    if (d > static_cast<double>(std::numeric_limits<int>::max()) ||
        d < static_cast<double>(std::numeric_limits<int>::min()) ||
        isnan(d))
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(d) << std::endl;

    std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(d) << "f" << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << d << std::endl;
}
