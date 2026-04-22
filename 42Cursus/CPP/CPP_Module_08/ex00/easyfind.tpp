/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:25:48 by tlima-de          #+#    #+#             */
/*   Updated: 2025/05/26 16:25:51 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "easyfind.hpp"

template <typename T>
typename T::iterator easyfind(T& container, int num) {
    typename T::iterator it = std::find(container.begin(), container.end(), num);
    if (it == container.end())
        throw NotFoundException();
    return it;
}

