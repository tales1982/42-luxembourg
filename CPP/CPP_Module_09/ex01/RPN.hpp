/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:12:36 by tales             #+#    #+#             */
/*   Updated: 2025/06/09 18:29:50 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// RPN.hpp
#ifndef RPN_HPP
#define RPN_HPP


#include <string>

class RPN {
public:
    static int evaluate(const std::string& expression);
};

#endif
