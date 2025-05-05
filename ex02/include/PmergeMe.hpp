/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csakamot <csakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:21:20 by csakamot          #+#    #+#             */
/*   Updated: 2024/09/28 16:24:38 by csakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#define SUCESCOLOR "\033[1;38;5;119m"
#define ERRORCOLOR "\033[1;38;5;196m"
#define RESETCOLOR "\033[0m"

#include <iostream>
#include <sstream>
#include <vector>

class PmergeMe {
private:
  std::vector<unsigned int> _array;

  PmergeMe(void);
  PmergeMe(const PmergeMe& obj);
  PmergeMe& operator=(const PmergeMe& obj);

  public:
  PmergeMe(std::vector<unsigned int> array);
  ~PmergeMe();
};

  std::ostream& operator<<(std::ostream& out, PmergeMe& obj);

#endif
