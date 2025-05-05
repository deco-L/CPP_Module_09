/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csakamot <csakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:21:20 by csakamot          #+#    #+#             */
/*   Updated: 2024/09/28 16:25:05 by csakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) {
  return ;
}

PmergeMe::PmergeMe(std::vector<unsigned int> array) {
  this->_array = array;
  return ;
}

PmergeMe::PmergeMe(const PmergeMe& obj) {
  *this = obj;
  return ;
}

PmergeMe::~PmergeMe() {
  return ;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& obj) {
  if (this != &obj) {
    ;
  }
  else
    std::cerr << ERRORCOLOR << "Error: "
              << "Attempted self-assignment in copy assignment operator"
              << RESETCOLOR
              << std::endl;
  return(*this);
}

std::ostream& operator<<(std::ostream& out, const PmergeMe& obj) {
  return (out);
}
