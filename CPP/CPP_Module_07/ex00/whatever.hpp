/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Whatever.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:04:33 by tales             #+#    #+#             */
/*   Updated: 2025/05/15 11:37:30 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
#define WHATEVER_HPP

template <typename T>
void swap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}

template <typename T>
const T& min(const T& a, const T& b) {
	return (a < b) ? a : b;
}

template <typename T>
const T& max(const T& a, const T& b) {
	return (a > b) ? a : b;
}

#endif
