/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:09:48 by tlima-de          #+#    #+#             */
/*   Updated: 2025/05/15 11:43:51 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

// =====================================================
// 		Construtores/Destrutores
// =====================================================
Serializer::Serializer(void){};
Serializer::Serializer(Serializer const &other){(void)other;};
Serializer &Serializer::operator=(Serializer const &other){ if (this != &other){} return *this;};
Serializer::~Serializer(void){};


// =====================================================
// 		Serializer auxiliary functions
// =====================================================
uintptr_t Serializer::serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw) {
    return reinterpret_cast<Data*>(raw);
}
