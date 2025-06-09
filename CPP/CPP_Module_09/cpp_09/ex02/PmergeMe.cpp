/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:03:16 by tales             #+#    #+#             */
/*   Updated: 2025/06/09 19:16:58 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// PmergeMe.cpp
#include "PmergeMe.hpp"
#include <sstream>
#include <ctime>
#include <algorithm>
#include <iomanip>

PmergeMe::PmergeMe(const std::vector<std::string>& args) {
    for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it) {
        std::istringstream iss(*it);
        int num;
        if (!(iss >> num) || num < 0)
            throw std::runtime_error("Invalid input: all arguments must be positive integers.");
        _vec.push_back(num);
        _deq.push_back(num);
    }
}

PmergeMe::~PmergeMe() {}

void PmergeMe::printVector(const std::vector<int>& vec, const std::string& label) const {
    if (!label.empty())
        std::cout << label;
    for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void PmergeMe::fordJohnsonSort(std::vector<int>& vec) {
    if (vec.size() <= 1)
        return;

    std::vector<int>::iterator mid = vec.begin() + vec.size() / 2;
    std::vector<int> left(vec.begin(), mid);
    std::vector<int> right(mid, vec.end());

    fordJohnsonSort(left);
    fordJohnsonSort(right);

    std::merge(left.begin(), left.end(), right.begin(), right.end(), vec.begin());
}

void PmergeMe::fordJohnsonSort(std::deque<int>& deq) {
    if (deq.size() <= 1)
        return;

    std::deque<int>::iterator mid = deq.begin() + deq.size() / 2;
    std::deque<int> left(deq.begin(), mid);
    std::deque<int> right(mid, deq.end());

    fordJohnsonSort(left);
    fordJohnsonSort(right);

    std::merge(left.begin(), left.end(), right.begin(), right.end(), deq.begin());
}

void PmergeMe::run() {
    std::cout << "\033[1;36mBefore:\033[0m ";
    printVector(_vec, "");

    std::clock_t startVec = std::clock();
    fordJohnsonSort(_vec);
    std::clock_t endVec = std::clock();

    std::clock_t startDeq = std::clock();
    fordJohnsonSort(_deq);
    std::clock_t endDeq = std::clock();

    std::cout << "\033[1;36mAfter:\033[0m ";
    printVector(_vec, "");

    double timeVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1e6;
    double timeDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1e6;

    std::cout << "\033[1;32mTime to process a range of " << _vec.size()
              << " elements with std::vector : \033[0m"
              << std::fixed << std::setprecision(2) << timeVec << " µs" << std::endl;

    std::cout << "\033[1;33mTime to process a range of " << _deq.size()
              << " elements with std::deque  : \033[0m"
              << std::fixed << std::setprecision(2) << timeDeq << " µs" << std::endl;
}
