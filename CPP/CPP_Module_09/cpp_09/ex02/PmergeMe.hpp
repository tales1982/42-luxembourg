/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:02:15 by tales             #+#    #+#             */
/*   Updated: 2025/06/09 19:16:51 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// PmergeMe.hpp
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <stdexcept>

class PmergeMe {
public:
    PmergeMe(const std::vector<std::string>& args);
    ~PmergeMe();

    void run();

private:
    std::vector<int> _vec;
    std::deque<int> _deq;

    void fordJohnsonSort(std::vector<int>& vec);
    void fordJohnsonSort(std::deque<int>& deq);
    void printVector(const std::vector<int>& vec, const std::string& label) const;
};

#endif

