/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csakamot <csakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:21:20 by csakamot          #+#    #+#             */
/*   Updated: 2024/09/24 14:29:29 by csakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::map<int, int> BitcoinExchange::initDates() {
    std::map<int, int> dates;
    dates.insert(std::make_pair(1, 31));
    dates.insert(std::make_pair(2, 28));
    dates.insert(std::make_pair(3, 31));
    dates.insert(std::make_pair(4, 30));
    dates.insert(std::make_pair(5, 31));
    dates.insert(std::make_pair(6, 30));
    dates.insert(std::make_pair(7, 31));
    dates.insert(std::make_pair(8, 31));
    dates.insert(std::make_pair(9, 30));
    dates.insert(std::make_pair(10, 31));
    dates.insert(std::make_pair(11, 30));
    dates.insert(std::make_pair(12, 31));
    return dates;
}

BitcoinExchange::BitcoinExchange(void) {
  this->_dates = initDates();
  return ;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& obj) {
  *this = obj;
  return ;
}

BitcoinExchange::~BitcoinExchange() {
  if (this->_file.is_open())
    this->_file.close();
  if (this->_input.is_open())
    this->_input.close();
  return ;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& obj)
{
  if (this != &obj) {
    ;
  }
  else
    std::cerr << "\e[1;31mBit Error: "
              << "Attempted self-assignment in copy assignment operator"
              << "\e[0m"
              << std::endl;
  return(*this);
}

BitcoinExchange::BitcoinExchangeError::BitcoinExchangeError(std::string error): _errorMessage(error) {
  return ;
}

BitcoinExchange::BitcoinExchangeError::~BitcoinExchangeError() _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
  return ;
}

const char* BitcoinExchange::BitcoinExchangeError::what(void) const throw() {
  return (this->_errorMessage.c_str());
}

void BitcoinExchange::inputExchangeRate(const std::string filePath) {
  struct stat buffer;

  if (filePath.find(".csv") != filePath.length() - 4)
    throw BitcoinExchange::BitcoinExchangeError("Error: Not csv file.");

  if (stat(filePath.c_str(), &buffer) == 0) {
    if (S_ISDIR(buffer.st_mode))
      throw BitcoinExchange::BitcoinExchangeError("Error: The directory path.");
  } else
    throw BitcoinExchange::BitcoinExchangeError("Error: The file does not exist.");
  this->_file.open(filePath.c_str());
  if (!this->_file.is_open())
    throw BitcoinExchange::BitcoinExchangeError("Error: could not open file.");

  std::string line;

  while (std::getline(this->_file, line)) {
    std::istringstream lineStream(line);
    std::string date;
    double rate;
    while (std::getline(lineStream, date, ',')) {
      lineStream >> rate;
      if (lineStream.fail())
        break ;
      this->_exchangeRate[date] = rate;
    }
  }
  return ;
}

static bool isLeapYear(int year) {
  if (year % 4 == 0) {
    if (year % 100 == 0 && year % 400 != 0) {
      return false;
    } else {
      return true;
    }
  }
  return false;
}

static bool gudgeMonth(int month) {
  if (1 <= month && month <=  12)
    return (false);
  return (true);
}

static bool gudgeDate(std::map<int, int> dates, int month, int day) {
  if (day <= dates[month])
    return (false);
  return (true);
}

static bool existDate(std::string date, std::map<int, int> dates) {
  std::vector<int> dateArray;
  std::string tmp;
  std::istringstream lineStream(date);

  while (std::getline(lineStream, tmp, '-')) {
    std::istringstream convert(tmp);
    int num;
    convert >> num;
    dateArray.push_back(num);
  }

  if (dateArray.size() != 3)
    return (false);
  if (dateArray[0] && isLeapYear(dateArray[0]))
    dates[9] = 29;
  else
    dates[9] = 28;
  if (dateArray[1] && gudgeMonth(dateArray[1]))
    return (false);
  if (dateArray[2] && gudgeDate(dates, dateArray[1], dateArray[2]))
    return (false);
  return (true);
}

void BitcoinExchange::showMultiplicationRate(std::string filePath) {
  struct stat buffer;

  if (filePath.find(".txt") != filePath.length() - 4)
    throw BitcoinExchange::BitcoinExchangeError("Error: Not txt file.");

  if (stat(filePath.c_str(), &buffer) == 0) {
    if (S_ISDIR(buffer.st_mode))
      throw BitcoinExchange::BitcoinExchangeError("Error: The directory path.");
  } else
    throw BitcoinExchange::BitcoinExchangeError("Error: The file does not exist.");
  this->_input.open(filePath.c_str());
  if (!this->_file.is_open())
    throw BitcoinExchange::BitcoinExchangeError("Error: could not open file.");

  std::string line;

  while (std::getline(this->_input, line)) {
    std::istringstream lineStream(line);
    std::string date;
    double rate;
    double multiplication;
    std::map<std::string, double>::iterator it;

    while (std::getline(lineStream, date, '|')) {
      lineStream >> rate;
      if (date == "date ")
        break ;
      if (
        lineStream.fail()
        || date.length() != 11
        || (date.length() == 11 && date[4] != '-' && date[7] != '-' && date[10] != ' ')
      ) {
        std::cerr << "Error: bad input => " << date << std::endl;
        break ;
      }
      if (rate < 0) {
        std::cerr << "Error: not a positive number." << std::endl;
        break ;
      }
      it = this->_exchangeRate.find(date);
      if (it == this->_exchangeRate.end()) {
        it = this->_exchangeRate.lower_bound(date);
        if (it != this->_exchangeRate.begin())
          it--;
      }
      multiplication = rate * it->second;
      if (!existDate(date, this->_dates)) {
        std::cerr << "Error: The date is invalid." << std::endl;
        break ;
      }
      if (0 <= multiplication && multiplication <= 1000)
        std::cout << date << "=> " << rate * it->second << std::endl;
      else
        std::cerr << "Error: too large a number." << std::endl;
    }
  }
  return ;
}

const std::ifstream& BitcoinExchange::getFile(void) const {
  return (this->_file);
}

std::map<std::string, double> BitcoinExchange::getExchangeRate(void) const {
  return (this->_exchangeRate);
}

int BitcoinExchange::getExchangeRate(std::string date) const {
  return (this->_exchangeRate.at(date));
}

void BitcoinExchange::showExchangeRate(void) {
  std::map<std::string, double>::iterator it = this->_exchangeRate.begin();
  while (it != this->_exchangeRate.end()) {
    std::cout << it->first << ":" << it->second << std::endl;
    ++it;
  }
  return ;
}
