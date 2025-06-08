/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csakamot <csakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:21:20 by csakamot          #+#    #+#             */
/*   Updated: 2025/06/08 19:15:28 by csakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cmath>

IndexedValue::IndexedValue(void) : value(0), index(0) {
  return ;
}

IndexedValue::IndexedValue(unsigned long val, size_t idx) : value(val), index(idx) {
  return ;
}

bool IndexedValue::operator<(const IndexedValue& other) const {
  return (this->value < other.value);
}

CompareWithCount::CompareWithCount(size_t& count) : comparisonCount(count) {
  return ;
}

bool CompareWithCount::operator()(const IndexedValue& a, const IndexedValue& b) {
  comparisonCount++;
  return a < b;
}

PmergeMe::PmergeMe(void) {
  return ;
}

PmergeMe::PmergeMe(const PmergeMe& obj) {
  *this = obj;
  return ;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& obj) {
  if (this != &obj) {
    ;
  }
  else
    std::cerr << "\033[1;31mBit Error: "
              << "Attempted self-assignment in copy assignment operator"
              << "\033[0m"
              << std::endl;
  return(*this);
}

PmergeMe::~PmergeMe() {
  return ;
}

std::vector<unsigned long> PmergeMe::makeJacobsthalSequence(unsigned long size) {
  std::vector<unsigned long> jacobsthalSequence;

  jacobsthalSequence.push_back(0);
  jacobsthalSequence.push_back(1);
  while (jacobsthalSequence.back() < size)
    jacobsthalSequence.push_back(
      std::pow(2, jacobsthalSequence.size()) - jacobsthalSequence.back()
    );
  if (jacobsthalSequence.back() > size)
    jacobsthalSequence.pop_back();
  jacobsthalSequence.erase(jacobsthalSequence.begin());
  return (jacobsthalSequence);
}

std::vector<std::pair<IndexedValue, IndexedValue> > PmergeMe::makePairs(const std::vector<IndexedValue>& indexedArray) {
  std::vector<std::pair<IndexedValue, IndexedValue> > pairArray;

  for (size_t i = 0; i < indexedArray.size() / 2; i++) {
    std::pair<IndexedValue, IndexedValue> element(indexedArray[2 * i], indexedArray[2 * i + 1]);

    pairArray.push_back(element);
  }
  if (indexedArray.size() % 2) {
    std::pair<IndexedValue, IndexedValue> element(indexedArray[indexedArray.size() - 1], IndexedValue(0, 0));

    pairArray.push_back(element);
  }
  return (pairArray);
}

void PmergeMe::sortPair(std::pair<IndexedValue, IndexedValue>& pair, size_t& comparisonCount) {
  if (pair.first.value < pair.second.value) {
    IndexedValue tmp = pair.first;

    pair.first = pair.second;
    pair.second = tmp;
  }
  comparisonCount++;
  return ;
}

void PmergeMe::sortPair(std::vector<IndexedValue>& pair, size_t& comparisonCount) {
  if (pair.size() != 2)
    return ;
  if (pair[0].value > pair[1].value) {
    IndexedValue tmp = pair[0];

    pair[0] = pair[1];
    pair[1] = tmp;
    comparisonCount++;
  }
  return ;
}

std::vector<std::pair<IndexedValue, IndexedValue> >::iterator PmergeMe::searchPairValue(const size_t& index, const std::vector<IndexedValue>& array, std::vector<std::pair<IndexedValue, IndexedValue> >& pairArray) {
  std::vector<std::pair<IndexedValue, IndexedValue> >::iterator it;

  if (index == array.size())
    return (pairArray.end() - 1);
  for (it = pairArray.begin(); it != pairArray.end(); ++it) {
    if (it->first.index == array[index].index)
      break ;
  }
  return (it);
}

std::vector<IndexedValue>::iterator PmergeMe::searchValue(std::vector<IndexedValue>& array, const size_t& index) {
  std::vector<IndexedValue>::iterator it;

  for (it = array.begin(); it != array.end(); ++it) {
    if (it->index == index)
      break ;
  }
  return (it);
}

void PmergeMe::insertValue(std::vector<IndexedValue>& array, std::vector<IndexedValue>::iterator position, std::vector<std::pair<IndexedValue, IndexedValue> >::iterator it) {
  if (it->second.index == 0)
    array.insert(position, it->first);
  else
    array.insert(position, it->second);
  return ;
}

void PmergeMe::mergeInsert(std::vector<IndexedValue>& array, std::vector<std::pair<IndexedValue, IndexedValue> >& pairArray, size_t& comparisonCount) {
  const std::vector<unsigned long> jacobsthalSequence = makeJacobsthalSequence(pairArray.size());
  std::vector<unsigned long>::const_iterator jacobsthalIter = jacobsthalSequence.begin();
  std::vector<std::pair<IndexedValue, IndexedValue> > tmpPairArray(pairArray);
  std::vector<IndexedValue> tmpArray(array);

  for (size_t i = 0; i < pairArray.size();) {
    if (jacobsthalIter == jacobsthalSequence.begin()) {
      std::vector<std::pair<IndexedValue, IndexedValue> >::iterator it = searchPairValue(*jacobsthalIter - 1, tmpArray, tmpPairArray);

      if (it == tmpPairArray.end())
        throw std::runtime_error("Error: Value not found in pair array");
      insertValue(array, array.begin(), it);
      tmpPairArray.erase(it);
      i++;
    } else if (jacobsthalIter != jacobsthalSequence.end()) {
      for (size_t j = 0; j < *jacobsthalIter - *(jacobsthalIter - 1); j++) {
        size_t index = *jacobsthalIter - j - 1;
        std::vector<std::pair<IndexedValue, IndexedValue> >::iterator it = searchPairValue(index, tmpArray, tmpPairArray);
        std::vector<IndexedValue>::iterator position;
        CompareWithCount comp(comparisonCount);

        if (it == tmpPairArray.end())
          throw std::runtime_error("Error: Value not found in pair array");
        if (it->second.index == 0)
          position = std::lower_bound(array.begin(), array.end(), it->first, comp);
        else
          position = std::lower_bound(array.begin(), searchValue(array, it->first.index), it->second, comp);
        insertValue(array, position, it);
        tmpPairArray.erase(it);
        i++;
      }
    } else {
      for (size_t j = 0; j < pairArray.size() - *(jacobsthalSequence.end() - 1); j++) {
        size_t index = pairArray.size() - j - 1;
        std::vector<std::pair<IndexedValue, IndexedValue> >::iterator it = searchPairValue(index, tmpArray, tmpPairArray);
        std::vector<IndexedValue>::iterator position;
        CompareWithCount comp(comparisonCount);

        if (it == tmpPairArray.end())
          throw std::runtime_error("Error: Value not found in pair array");
        if (it->second.index == 0)
          position = std::lower_bound(array.begin(), array.end(), it->first, comp);
        else
          position = std::lower_bound(array.begin(), searchValue(array, it->first.index), it->second, comp);
        insertValue(array, position, it);
        tmpPairArray.erase(it);
        i++;
      }
    }
    jacobsthalIter++;
  }
  return ;
}

std::vector<IndexedValue> PmergeMe::fordJohnsonAlgorithm(std::vector<IndexedValue> indexedArray, size_t& comparisonCount) {
  std::vector<std::pair<IndexedValue, IndexedValue> > pairArray = makePairs(indexedArray);
  std::vector<IndexedValue> largerArray;
  std::vector<IndexedValue> sortedArray;

  if (indexedArray.size() > 2) {
    for (size_t i = 0; i < pairArray.size(); i++) {
      if (pairArray[i].first.value == 0 || pairArray[i].second.value == 0)
        break ;
      sortPair(pairArray[i], comparisonCount);
      largerArray.push_back(pairArray[i].first);
    }
    sortedArray = fordJohnsonAlgorithm(largerArray, comparisonCount);
    mergeInsert(sortedArray, pairArray, comparisonCount);
  } else if (indexedArray.size() == 2) {
    sortPair(indexedArray, comparisonCount);
    return (indexedArray);
  } else
    return (indexedArray);
  return (sortedArray);
}

// size_t PmergeMe::ford_johnson_algorithm(std::list<unsigned long>& array) {
//   size_t comparison_count = 0;

//   return (comparison_count);
// }
