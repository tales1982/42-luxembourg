/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:35:02 by tlima-de          #+#    #+#             */
/*   Updated: 2025/05/16 12:38:26 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ITER_HPP
#define ITER_HPP

template <typename T>
void iter(T *array, int length, void (*func)(T const &)) {
	for (int i = 0; i < length; ++i)
		func(array[i]);
}



#endif
