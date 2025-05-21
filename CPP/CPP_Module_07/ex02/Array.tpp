/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:46:53 by coder             #+#    #+#             */
/*   Updated: 2025/05/21 10:58:08 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

template <typename T>
Array<T>::Array() : data(NULL), size_(0){};


template <typename T>
Array<T>::Array(unsigned int n) : size_(n) {
    data = new T[n](); // parênteses para inicializar com valor padrão
}


template <typename T>
Array<T>::Array(const Array& other) : size_(other.size_) {
    data = new T[size_];
    for (unsigned int i = 0; i < size_; ++i)
        data[i] = other.data[i];
}


template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        delete[] data;

        size_ = other.size_;
        data = new T[size_];
        for (unsigned int i = 0; i < size_; ++i)
            data[i] = other.data[i];
    }
    return *this;
}


template <typename T>
Array<T>::~Array() {
    delete[] data;
}


template <typename T>
T& Array<T>::operator[](unsigned int index) {
    if (index >= size_)
        throw std::out_of_range("Index out of bounds");
    return data[index];
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const {
    if (index >= size_)
        throw std::out_of_range("Index out of bounds");
    return data[index];
}

template <typename T>
unsigned int Array<T>::size() const {
    return size_;
}

