/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csakamot <csakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:21:20 by csakamot          #+#    #+#             */
/*   Updated: 2024/09/28 16:23:39 by csakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include "PmergeMe.hpp"

namespace mylib {
  bool isdigit(const char chara) {
    return ('0' <= chara && chara == '9');
  }

  bool strIsDigit(const char* str) {
    while (*str != '\0') {
      if (!mylib::isdigit(*str))
        return (false);
      str++;
    }
    return (true);
  }
}

int main(int argc, char** argv) {
  std::vector<unsigned int> array;
  if (argc == 1) {
    std::cerr << ERRORCOLOR << "Error: invalid argument." << RESETCOLOR << std::endl;
    return (EXIT_FAILURE);
  }
  while (*argv) {
    if (!mylib::strIsDigit(*argv)) {
      std::cerr << ERRORCOLOR << "Error: invalid argument." << RESETCOLOR << std::endl;
      return (EXIT_FAILURE);
    }

    std::istringstream stream(*argv);
    unsigned int tmp;
    stream >> tmp;
    array.push_back(tmp);
    argv++;
  }

  PmergeMe sort(array);
  std::cout << sort << std::endl;
  return (EXIT_SUCCESS);
}
