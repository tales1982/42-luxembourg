/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:46:49 by coder             #+#    #+#             */
/*   Updated: 2025/05/21 11:03:43 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>
#include <cstdlib> // para srand e rand
#include <ctime>   // para time


template <typename T>
class Array {
private:
    T* data;
    unsigned int size_;

public:
    Array();                                   // construtor vazio
    Array(unsigned int n);                     // construtor com tamanho
    Array(const Array& other);                 // construtor de cópia
    Array& operator=(const Array& other);      // operador de atribuição
    ~Array();                                  // destrutor

    T& operator[](unsigned int index);         // acesso com verificação
    const T& operator[](unsigned int index) const;

    unsigned int size() const;                 // retorna tamanho do array
};

#include "Array.tpp" // inclui a implementação 

#endif
