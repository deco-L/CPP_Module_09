/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csakamot <csakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:21:20 by csakamot          #+#    #+#             */
/*   Updated: 2024/09/23 02:59:18 by csakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <unistd.h>
#include "BitcoinExchange.hpp"

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

int main(int argc, char** argv) {
	draw_terminal_line();
  if (argc != 2) {
		std::cout << "\033[1;38;5;196mError: could not file.\033[0m" <<std::endl;
		draw_terminal_line();
    return(EXIT_FAILURE);
	}
	try {
		BitcoinExchange bitCoin;

		bitCoin.inputExchangeRate("./src/data.csv");
		bitCoin.showMultiplicationRate(argv[1]);
	}
	catch(const std::exception& e) {
		std::cerr << "\033[38;5;196m" << e.what() << "\033[0m" << std::endl;
	}
	
	draw_terminal_line();
  return (EXIT_SUCCESS);
}
