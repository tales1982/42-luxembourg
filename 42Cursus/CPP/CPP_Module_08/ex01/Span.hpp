/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:45:48 by tlima-de          #+#    #+#             */
/*   Updated: 2025/05/27 10:45:51 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <iostream>
#include <exception>
#include <stdexcept>   // std::logic_error
#include <algorithm>   // std::sort, std::min_element, std::max_element
#include <cstdlib>     // std::abs
#include <cstddef>     // std::size_t


class Span {
private:
    unsigned int _maxSize;
    std::vector<int> _numbers;

public:
    // Canonical Orthodox Form
    Span();                                  // Construtor padrão
    Span(unsigned int n);                    // Construtor parametrizado
    Span(const Span& other);                 // Construtor de cópia
    Span& operator=(const Span& other);      // Operador de atribuição
    ~Span();                                 // Destrutor

    // Funções principais
    void addNumber(int number);
 

    int shortestSpan() const;
    int longestSpan() const;

    // Exceções customizadas
    class FullSpanException : public std::exception {
    public:
        virtual const char* what() const throw();
    };

    class NotEnoughNumbersException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
};


#endif

