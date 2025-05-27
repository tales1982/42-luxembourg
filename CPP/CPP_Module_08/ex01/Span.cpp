/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:47:48 by tlima-de          #+#    #+#             */
/*   Updated: 2025/05/27 10:47:51 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"


Span::Span() : _maxSize(0) , _numbers() {};

Span::Span(unsigned int n) : _maxSize(n), _numbers() {}; 

Span::Span(const Span& other) : _maxSize(other._maxSize), _numbers(other._numbers) {}

Span& Span::operator=(const Span& other) {
    if (this != &other) {
        _maxSize = other._maxSize;
        _numbers = other._numbers;
    }
    return *this;
}


Span::~Span() {}

// Adiciona um número
void Span::addNumber(int number) {
    if (_numbers.size() >= _maxSize)
        throw FullSpanException();
    _numbers.push_back(number);
}


int Span::shortestSpan() const {
    if (_numbers.size() < 2)
        throw std::logic_error("Not enough elements to find a span");

    std::vector<int> tmp = _numbers;
    std::sort(tmp.begin(), tmp.end());

    int minSpan = std::abs(tmp[1] - tmp[0]);
    for (size_t i = 1; i < tmp.size() - 1; ++i) {
        int span = std::abs(tmp[i + 1] - tmp[i]);
        if (span < minSpan)
            minSpan = span;
    }
    return minSpan;
}


int Span::longestSpan() const {
    if (_numbers.size() < 2)
        throw std::logic_error("Not enough elements to find a span");

    int min = *std::min_element(_numbers.begin(), _numbers.end());
    int max = *std::max_element(_numbers.begin(), _numbers.end());
    return max - min;
}


// Exceções customizadas
const char* Span::FullSpanException::what() const throw() {
    return "Span is already full!";
}

const char* Span::NotEnoughNumbersException::what() const throw() {
    return "Not enough numbers to find a span!";
}
