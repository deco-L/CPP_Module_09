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
#include <sys/ioctl.h>
#include <unistd.h>

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

  static std::vector<unsigned long> parse_argv_to_vector(int argc, char** argv) {
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

  static std::vector<IndexedValue> vector_to_indexed_vector(std::vector<unsigned long>& array) {
    std::vector<IndexedValue> indexed_vector;

    for (size_t i = 0; i < array.size(); i++) {
      IndexedValue indexed_value(array[i], i + 1);
      indexed_vector.push_back(indexed_value);
    }
    return (indexed_vector);
  }

  static std::vector<unsigned long> indexedVectorToVector(const std::vector<IndexedValue>& indexed_vector) {
    std::vector<unsigned long> array;

    for (size_t i = 0; i < indexed_vector.size(); i++)
      array.push_back(indexed_vector[i].value);
    return (array);
  }
  // static std::list<unsigned long> parse_argv_to_list(int argc, char** argv);
}

int main(int argc, char** argv) {
  mylib::draw_terminal_line();
  if (!mylib::is_valid_arguments(argc, argv))
    return (mylib::draw_terminal_line(), EXIT_FAILURE);
  try {
    {
      std::vector<unsigned long> numSequence;
      size_t comparisonCount = 0;
      std::vector<IndexedValue> sorted;

      numSequence = mylib::parse_argv_to_vector(argc, argv);
      std::cout << "Before:\t";
      PmergeMe::display_array(numSequence);
      std::cout << std::endl;
      sorted = PmergeMe::fordJohnsonAlgorithm(mylib::vector_to_indexed_vector(numSequence), comparisonCount);
      std::cout << SUCESCOLOR << "Number of comparisons: " << comparisonCount << RESETCOLOR << std::endl;
      std::cout << "After:\t";
      PmergeMe::display_array(mylib::indexedVectorToVector(sorted));
      std::cout << std::endl;
    }
  } catch (const std::exception& e) {
    std::cerr << ERRORCOLOR << e.what() << RESETCOLOR << std::endl;
    return (mylib::draw_terminal_line(), EXIT_FAILURE);
  }
  return (mylib::draw_terminal_line(), EXIT_SUCCESS);
}
