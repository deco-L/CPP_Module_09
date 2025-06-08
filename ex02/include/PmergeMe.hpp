/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csakamot <csakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:21:20 by csakamot          #+#    #+#             */
/*   Updated: 2025/06/08 19:05:26 by csakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#define SUCESCOLOR "\033[1;38;5;119m"
#define ERRORCOLOR "\033[1;38;5;196m"
#define RESETCOLOR "\033[0m"

#include <cstdlib>
#include <cerrno>
#include <climits>
#include <sstream>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

struct IndexedValue {
  unsigned long value;
  size_t index;

  IndexedValue(void);
  IndexedValue(unsigned long val, size_t idx);
  bool operator<(const IndexedValue& other) const;
};

struct CompareWithCount {
  size_t& comparisonCount;

public:
  CompareWithCount(size_t& count);
  bool operator()(const IndexedValue& a, const IndexedValue& b);
};
class PmergeMe {
private:
  PmergeMe(void);
  PmergeMe(const PmergeMe& obj);
  PmergeMe& operator=(const PmergeMe& obj);
  ~PmergeMe();

  static std::vector<unsigned long> makeJacobsthalSequence(unsigned long size);
  static std::vector<std::pair<IndexedValue, IndexedValue> > makePairs(const std::vector<IndexedValue>& indexedValue);
  static void sortPair(std::pair<IndexedValue, IndexedValue>& pair, size_t& comparisonCount);
  static void sortPair(std::vector<IndexedValue>& pair, size_t& comparisonCount);
  static std::vector<std::pair<IndexedValue, IndexedValue> >::iterator searchPairValue(const size_t& index, const std::vector<IndexedValue>& array, std::vector<std::pair<IndexedValue, IndexedValue> >& pairArray);
  static std::vector<IndexedValue>::iterator searchValue(std::vector<IndexedValue>& array, const size_t& index);
  static void insertValue(std::vector<IndexedValue>& array, std::vector<IndexedValue>::iterator position, std::vector<std::pair<IndexedValue, IndexedValue> >::iterator it);
  static void mergeInsert(std::vector<IndexedValue>& array, std::vector<std::pair<IndexedValue, IndexedValue> >& pairArray, size_t& comparisonCount);

public:
  template <typename T>
  static void display_array(const T& array) {
    for (typename T::const_iterator it = array.begin(); it != array.end(); ++it) {
      if (it != array.begin())
        std::cout << ' ';
      if (array.size() > 5 && it - array.begin() == 4) {
        std::cout << "[...]";
        return ;
      }
      std::cout << *it;
    }
    return ;
  }
  static std::vector<IndexedValue> fordJohnsonAlgorithm(std::vector<IndexedValue> indexedArray, size_t& comparisonCount);
  // static size_t ford_johnson_algorithm(std::list<unsigned long>& array);
};

#endif
