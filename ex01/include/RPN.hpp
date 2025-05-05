/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csakamot <csakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:21:20 by csakamot          #+#    #+#             */
/*   Updated: 2024/11/30 20:23:28 by csakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#define SUCESCOLOR "\033[1;38;5;119m"
#define ERRORCOLOR "\033[1;38;5;196m"
#define RESETCOLOR "\033[0m"

#include <cstdlib>
#include <iostream>
#include <stack>

class RPN {
private:
  std::stack<double> _data;

  RPN(const RPN& obj);
  RPN& operator=(const RPN& obj);

public:
  RPN(void);
  ~RPN();

  void push(const double& nbr);
  void pop(void);
  bool empty(void);
  const double& top(void) const;
  bool calcu(const std::string& opt, const double& nbr);
  double operator+(const double& nbr) const;
  double operator-(const double& nbr) const;
  double operator*(const double& nbr) const;
  double operator/(const double& nbr) const;
};

#endif
