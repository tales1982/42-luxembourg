/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:25:48 by tlima-de          #+#    #+#             */
/*   Updated: 2025/05/26 16:25:51 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm> // std::find
#include <exception> // std::exception

template <typename T>
typename T::iterator easyfind(T& container, int num);

class NotFoundException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Element not found";
    }
};

#include "easyfind.tpp"

#endif

