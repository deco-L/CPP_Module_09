/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csakamot <csakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:21:20 by csakamot          #+#    #+#             */
/*   Updated: 2024/09/23 07:21:27 by csakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <cstdlib>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

class BitcoinExchange
{
private:
  std::ifstream _file;
  std::ifstream _input;
  std::map<std::string, double> _exchangeRate;
  std::map<int, int> _dates;

  BitcoinExchange(const BitcoinExchange& obj);
  BitcoinExchange& operator=(const BitcoinExchange& obj);

public:

  BitcoinExchange(void);
  ~BitcoinExchange();

  class BitcoinExchangeError : public std::exception {
  private:
    std::string _errorMessage;
  
  public:
    BitcoinExchangeError(std::string error);
    virtual ~BitcoinExchangeError() _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW;
    virtual const char* what(void) const throw();
  };

  std::map<int, int> initDates();
  void inputExchangeRate(const std::string filePath);
  const std::ifstream& getFile(void) const;
  std::map<std::string, double> getExchangeRate(void) const;
  int getExchangeRate(std::string date) const;
  void showExchangeRate(void);
  void showMultiplicationRate(std::string filePath);
};

#endif
