/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csakamot <csakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:21:20 by csakamot          #+#    #+#             */
/*   Updated: 2025/06/08 17:27:37 by csakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

namespace mylib {
  static size_t get_term_line() {
    winsize	terminal_size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminal_size);
    return (terminal_size.ws_col);
  }

  static void draw_terminal_line() {
    size_t	terminal_col;

    terminal_col = get_term_line();
    for (size_t i = 0; i < terminal_col; i++)
      std::cout << "=";
    std::cout << std::endl;
    return ;
  }

  static bool is_valid_arguments(const int argc, char** argv) {
    if (argc <= 1)
      return (
        std::cerr << ERRORCOLOR << "Error: invalid argument."
                  << RESETCOLOR << std::endl,
        false
      );
    for (int i = 1; i < argc; i++) {
      char* endptr;
      unsigned long tmp = std::strtoul(argv[i], &endptr, 10);

      if (endptr == argv[i]) {
        return (
          std::cerr << ERRORCOLOR << "Error: not a number."
                    << RESETCOLOR << std::endl,
          false
        );
      }
      if (argv[i][0] == '-') {
        return (
          std::cerr << ERRORCOLOR << "Error: negative number is not allowed."
                    << RESETCOLOR << std::endl,
          false
        );
      }
      if ((errno == ERANGE && tmp == ULONG_MAX)) {
        return (
          std::cerr << ERRORCOLOR << "Error: number too large."
                    << RESETCOLOR << std::endl,
          false
        );
      }
      if (*endptr != '\0') {
        return (
          std::cerr << ERRORCOLOR << "Error: invalid character after number."
                    << RESETCOLOR << std::endl,
          false
        );
      }
    }
    return (true);
  }

  static std::vector<unsigned long> parseArgvToVector(
      int argc,
      char** argv
      ) {
    std::vector<unsigned long> array;

    for (int i = 1; i < argc; i++) {
      char* endptr;
      unsigned long tmp = std::strtoul(argv[i], &endptr, 10);

      if (endptr == argv[i]) {
        return (
          std::cerr << ERRORCOLOR << "Error: not a number."
                    << RESETCOLOR << std::endl,
          std::vector<unsigned long>(0, 0)
        );
      }
      if (argv[i][0] == '-') {
        return (
          std::cerr << ERRORCOLOR << "Error: negative number is not allowed."
                    << RESETCOLOR << std::endl,
          std::vector<unsigned long>(0, 0)
        );
      }
      if ((errno == ERANGE && tmp == ULONG_MAX)) {
        return (
          std::cerr << ERRORCOLOR << "Error: number too large."
                    << RESETCOLOR << std::endl,
          std::vector<unsigned long>(0, 0)
        );
      }
      if (*endptr != '\0') {
        std::cerr << "Error: invalid character after number." << std::endl;
        return (
          std::cerr << ERRORCOLOR << "Error: invalid character after number."
                    << RESETCOLOR << std::endl,
          std::vector<unsigned long>(0, 0)
        );
      }
      array.push_back(tmp);
    }
    return (array);
  }

  static std::list<unsigned long> parseArgvToList(
      int argc,
      char** argv
      ) {
    std::list<unsigned long> array;

    for (int i = 1; i < argc; i++) {
      char* endptr;
      unsigned long tmp = std::strtoul(argv[i], &endptr, 10);

      if (endptr == argv[i]) {
        return (
          std::cerr << ERRORCOLOR << "Error: not a number."
                    << RESETCOLOR << std::endl,
          std::list<unsigned long>(0, 0)
        );
      }
      if (argv[i][0] == '-') {
        return (
          std::cerr << ERRORCOLOR << "Error: negative number is not allowed."
                    << RESETCOLOR << std::endl,
          std::list<unsigned long>(0, 0)
        );
      }
      if ((errno == ERANGE && tmp == ULONG_MAX)) {
        return (
          std::cerr << ERRORCOLOR << "Error: number too large."
                    << RESETCOLOR << std::endl,
          std::list<unsigned long>(0, 0)
        );
      }
      if (*endptr != '\0') {
        std::cerr << "Error: invalid character after number." << std::endl;
        return (
          std::cerr << ERRORCOLOR << "Error: invalid character after number."
                    << RESETCOLOR << std::endl,
          std::list<unsigned long>(0, 0)
        );
      }
      array.push_back(tmp);
    }
    return (array);
  }

  static std::vector<IndexedValue> vectorToIndexedVector(
      std::vector<unsigned long> array
      ) {
    std::vector<IndexedValue> indexedVector;

    for (size_t i = 0; i < array.size(); i++) {
      IndexedValue indexedValue(array[i], i + 1);

      indexedVector.push_back(indexedValue);
    }
    return (indexedVector);
  }

  static std::list<IndexedValue> listToIndexedList(
      std::list<unsigned long> array
      ) {
    std::list<IndexedValue> indexedList;
    size_t index = 1;

    for (std::list<unsigned long>::iterator it = array.begin(); it != array.end(); it++) {
      IndexedValue indexedValue(*it, index++);

      indexedList.push_back(indexedValue);
    }
    return (indexedList);
  }

  static std::vector<unsigned long> indexedVectorToVector(
      const std::vector<IndexedValue>& indexedVector
      ) {
    std::vector<unsigned long> array;

    for (size_t i = 0; i < indexedVector.size(); i++)
      array.push_back(indexedVector[i].value);
    return (array);
  }

  static std::list<unsigned long> indexedListToList(
      const std::list<IndexedValue>& indexedList
      ) {
    std::list<unsigned long> array;

    for (std::list<IndexedValue>::const_iterator it = indexedList.begin(); it != indexedList.end(); it++)
      array.push_back(it->value);
    return (array);
  }

  double getTimeSec(void) {
      struct timeval tv;
      gettimeofday(&tv, NULL);

      return (tv.tv_sec + tv.tv_usec / 1e6);
  }
}

int main(int argc, char** argv) {
  mylib::draw_terminal_line();
  if (!mylib::is_valid_arguments(argc, argv))
    return (mylib::draw_terminal_line(), EXIT_FAILURE);
  try {
    {
      std::vector<IndexedValue> numSequence;
      std::vector<IndexedValue> sorted;
      size_t comparisonCount = 0;
      double start;
      double end;

      start = mylib::getTimeSec();
      numSequence = mylib::vectorToIndexedVector(
          mylib::parseArgvToVector(argc, argv)
          );
      if (mylib::indexedVectorToVector(numSequence).size() > 3000) {
        return (
            std::cerr << ERRORCOLOR << "Error: too many elements."
                  << RESETCOLOR << std::endl,
                  EXIT_FAILURE
            );
      }
      std::cout << "Before:\t";
      PmergeMe::displayArray(mylib::indexedVectorToVector(numSequence));
      std::cout << std::endl;
      sorted = PmergeMe::fordJohnsonAlgorithm(
          numSequence,
          comparisonCount
          );
      end = mylib::getTimeSec(); 
      std::cout << "After:\t";
      PmergeMe::displayArray(mylib::indexedVectorToVector(sorted));
      std::cout << std::endl;
      // std::cout << "Number of comparisons: " << comparisonCount << std::endl;
      std::cout << "Time to process a range of\t"
                << mylib::indexedVectorToVector(numSequence).size()
                << " elements with std::vector:\t"
                << std::fixed << std::setprecision(5)
                << end - start << "us" << std::endl;
    }
    {
      std::list<IndexedValue> numSequence;
      std::list<IndexedValue> sorted;
      size_t comparisonCount = 0;
      double start;
      double end;

      start = mylib::getTimeSec();
      numSequence = mylib::listToIndexedList(
          mylib::parseArgvToList(argc, argv)
          );
      // std::cout << "Before:\t";
      // PmergeMe::displayArray(mylib::indexedListToList(numSequence));
      // std::cout << std::endl;
      sorted = PmergeMe::fordJohnsonAlgorithm(
          numSequence,
          comparisonCount
          );
      end = mylib::getTimeSec(); 
      // std::cout << "After:\t";
      // PmergeMe::displayArray(mylib::indexedListToList(sorted));
      // std::cout << std::endl;
      // std::cout << "Number of comparisons: " << comparisonCount << std::endl;
      std::cout << "Time to process a range of\t"
                << mylib::indexedListToList(numSequence).size()
                << " elements with std::list:\t"
                << std::fixed << std::setprecision(5)
                << end - start << "us" << std::endl;
    }
  } catch (const std::exception& e) {
    std::cerr << ERRORCOLOR << e.what() << RESETCOLOR << std::endl;
    return (mylib::draw_terminal_line(), EXIT_FAILURE);
  }
  return (mylib::draw_terminal_line(), EXIT_SUCCESS);
}

