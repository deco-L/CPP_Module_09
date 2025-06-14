/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csakamot <csakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:21:20 by csakamot          #+#    #+#             */
/*   Updated: 2024/09/26 04:10:16 by csakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>

static bool gudgeOperator(const std::string str) {
  return (str == "+" || str == "-" || str == "*" || str == "/");
}

int main(int argc, char** argv) {
  RPN rpn;
  double tmp;
  std::string element;

  if (argc != 2) {
    std::cerr << ERRORCOLOR << "Error: Invalid arguments." << RESETCOLOR << std::endl;
    return (EXIT_FAILURE);
  }
  std::istringstream lineStream(argv[1]);
  if (!*argv[1]) {
    std::cerr << ERRORCOLOR << "Error: Invalid arguments." << RESETCOLOR << std::endl;
    return (EXIT_FAILURE);
  }
  while (std::getline(lineStream, element, ' ')) {
    std::istringstream strToD(element);
    strToD >> tmp;
    if (strToD.fail() && !gudgeOperator(element)) {
      std::cerr << ERRORCOLOR << "Error: invalid argument." << RESETCOLOR << std::endl;
      return (EXIT_FAILURE);
    } else if (strToD.fail() && gudgeOperator(element)) {
      if (!rpn.calcu(element)) {
        std::cerr << ERRORCOLOR << "Error: invalid argument." << RESETCOLOR << std::endl;
        return (EXIT_FAILURE);
      }
    } else
      rpn.push(tmp);
  }
  if (rpn.size() > 1) {
    std::cerr << ERRORCOLOR << "Error: Invalid arguments." << RESETCOLOR << std::endl;
    return (EXIT_FAILURE);
  }
  std::cout << SUCESCOLOR << "Result: " << RESETCOLOR << rpn.top() << std::endl;
  return (EXIT_SUCCESS);
}

