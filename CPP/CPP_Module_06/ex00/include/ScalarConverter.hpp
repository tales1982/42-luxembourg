/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:04:33 by tales             #+#    #+#             */
/*   Updated: 2025/05/05 21:05:14 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <cctype>

#include <math.h>


class ScalarConverter
{
private:
	// Construtor, destrutor e operadores privados para impedir instanciação
	ScalarConverter();
	ScalarConverter(const ScalarConverter &);
	ScalarConverter &operator=(const ScalarConverter &);
	~ScalarConverter();

public:
	// Método estático principal que será chamado a partir do main
	static void convert(const std::string &literal);
	static bool isInt(const std::string &literal);
	static bool isFloat(const std::string &literal);
	static bool isDouble(const std::string &literal);

	static void convertFromChar(char c);
	static void convertFromInt(int i);
	static void convertFromFloat(float f);
	static void convertFromDouble(double d);
};

#endif
