/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:17:27 by tlima-de          #+#    #+#             */
/*   Updated: 2025/06/02 14:17:30 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// MutantStack.hpp
#pragma once
#include <stack>
#include <deque>
#include <iostream>

// Template class that inherits from std::stack and exposes iterators

template <typename T>
class MutantStack : public std::stack<T> {
public:
    MutantStack() {}
    MutantStack(const MutantStack& other) : std::stack<T>(other) {}
    ~MutantStack() {}

    MutantStack& operator=(const MutantStack& other) {
        std::stack<T>::operator=(other);
        return *this;
    }

    typedef typename std::stack<T>::container_type::iterator iterator;

    iterator begin() { return this->c.begin(); }
    iterator end()   { return this->c.end();   }
};
