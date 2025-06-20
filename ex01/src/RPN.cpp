/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csakamot <csakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:21:20 by csakamot          #+#    #+#             */
/*   Updated: 2024/09/26 04:21:54 by csakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void) {
  return ;
}

RPN::RPN(const RPN& obj) {
  *this = obj;
}

RPN::~RPN() {
  return ;
}

RPN& RPN::operator=(const RPN& obj) {
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

void RPN::push(const double& nbr) {
  return (this->_data.push(nbr));
}

size_t RPN::size(void) {
  return (this->_data.size());
}

void RPN::pop(void) {
  if (!this->_data.empty())
    this->_data.pop();
  else
    std::cerr << ERRORCOLOR << "Error: stack in empty" << RESETCOLOR << std::endl;
  return ;
}

bool RPN::empty(void) {
  return (this->_data.empty());
}

const double& RPN::top(void) const {
  return (this->_data.top());
}

bool RPN::calcu(const std::string& opt) {
  double tmp;

  if (this->size() >= 2) {
    tmp = this->top();
    this->pop();
  } else
    return (false);
  switch (opt.c_str()[0])
  {
  case '+':
    *this + tmp;
    break ;

  case '-':
    *this - tmp;
    break ;

  case '*':
    *this * tmp;
    break ;

  case '/':
    *this / tmp;
    break ;

  default:
    std::cerr << ERRORCOLOR << "That operator is not supported." << RESETCOLOR << std::endl;
    return (false);
  }
  return (true);
}

double RPN::operator+(const double& nbr) {
  double result;

  result = this->top() + nbr;
  this->pop();
  this->push(result);
  return (result);
}

double RPN::operator-(const double& nbr) {
  double result;

  result = this->top() - nbr;
  this->pop();
  this->push(result);
  return (result);
}

double RPN::operator*(const double& nbr) {
  double result = this->top();

  result = this->top() * nbr;
  this->pop();
  this->push(result);
  return (result);
}

double RPN::operator/(const double& nbr) {
  double result;

  result = this->top() / nbr;
  this->pop();
  this->push(result);
  return (result);
}

