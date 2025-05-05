# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csakamot <csakamot@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/01 14:21:20 by csakamot          #+#    #+#              #
#    Updated: 2024/09/29 18:26:46 by csakamot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL		= bash

##----Executable File Name-----##
NAME		= RPN
##-----------------------------##

##-----Directory Location------##
SRCDIR	= ./src/

INCDIR	= ./include/

OBJDIR	= objs/
##-----------------------------##

##------------Srcs-------------##
MAINSRC	=	main.cpp RPN.cpp

SRCS		= $(addprefix $(SRCDIR), ${MAINSRC})
##-----------------------------##

##-----------Object------------##
OBJS		= ${subst ${SRCDIR}, $(OBJDIR), ${SRCS:.cpp=.o}}
##-----------------------------##

##----------conpiler-----------##
CC			= c++
CFLAGS	= -Wall -Wextra -Werror -std=c++98 -fsanitize=address
##-----------------------------##

##-----------archive-----------##
ARFLAG	= rcs
##-----------------------------##

##-------escape sequence-------##
RED			= \e[38;5;1m
GREEN		= \e[38;5;2m
ORANGE	= \e[38;5;3m
BLUE		= \e[38;5;4m
VIOLET	= \e[38;5;5m
AQUA		= \e[38;5;6m
WHITE		= \e[38;5;7m
GREY		= \e[38;5;8m
SET1		= \e[1;38;5;51m
RESET		= \e[0m
##-----------------------------##

##--------set variable---------##
COUNT		= 0
FILES		= 0
RATE		= 0.0
BAR			= 70
##-----------------------------##

##--------Makefile rule--------##
all:prev ${NAME}

prev:
				@$(eval FILES = $(shell find . -name "*.cpp" | wc -l))

${NAME}:${OBJS}
				@printf	"\n"
				@printf "$(SET1)                                        ,e, 888              888 888 888 $(RESET)\n"
				@printf "$(SET1) e88\'888  e88 88e  888 888 8e  888 88e   \"  888  ,e e,   e88 888 888 888 $(RESET)\n"
				@printf "$(SET1)d888  \'8 d888 888b 888 888 88b 888 888b 888 888 d88 88b d888 888 \"8\" \"8\" $(RESET)\n"
				@printf "$(SET1)Y888   , Y888 888P 888 888 888 888 888P 888 888 888   , Y888 888  e   e  $(RESET)\n"
				@printf "$(SET1) \"88,e8\'  \"88 88\"  888 888 888 888 88\"  888 888  \"YeeP\"  \"88 888 \"8\" \"8\" $(RESET)\n"
				@printf "$(SET1)                               888                                       $(RESET)\n"
				@printf "$(SET1)                               888                                       $(RESET)\n"
				@$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)%.o:$(SRCDIR)%.cpp
				@printf "\r\e[0m"
				@$(eval COUNT = $(shell echo $$(($(COUNT) + 1))))
				@printf "["
				@$(eval RATE = $(shell echo "scale=2; $(COUNT) / $(FILES) * $(BAR)" | bc | awk '{print int($$1)}'))
				@for i in {1..$(BAR)}; \
					do if [ $$i -le $(RATE) ]; \
						then printf "$(AQUA)=\e$(RESET)"; \
					else printf " "; \
					fi; \
				done
				@printf "]"
				@mkdir -p $(OBJDIR)
				@$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

clean:
				@${RM} -rf ${OBJDIR}
				@printf "\e[38;5;197mobject file removed\e[0m\n"

fclean:clean
				@${RM} -rf ${NAME}
				@printf "\e[38;5;197mexecutable file removed\e[0m\n"

re:fclean all

exe:re
				@make -s clean

test:re
		@echo "$(GREEN)Test 1:$(NC)"
		./$(NAME) "3 4 +"
		@echo "$(GREEN)Test 2:$(NC)"
		./$(NAME) "10 2 -"
		@echo "$(GREEN)Test 3:$(NC)"
		./$(NAME) "6 7 *"
		@echo "$(GREEN)Test 4:$(NC)"
		./$(NAME) "210 7 /"
		@echo "$(GREEN)Test 5:$(NC)"
		./$(NAME) "5 1 2 + 4 * + 3 -"
		@echo "$(GREEN)Test 6:$(NC)"
		./$(NAME) "3.5 2.1 + 3.2 4.7 - *"
		@echo "$(GREEN)Test 7:$(NC)"
		./$(NAME) "3 4 + 5 2 - *"
		@echo "$(GREEN)Test 8:$(NC)"
		./$(NAME) "6 2 + 5 * 3 - 4 /"
		@echo "$(GREEN)Test 9:$(NC)"
		./$(NAME) "7 2 3 + 4 * + 5 -"
		@echo "$(GREEN)Test 10:$(NC)"
		./$(NAME) "3.5 2.5 + 8 3.2 - *"
		@echo "$(GREEN)Test 11:$(NC)"
		./$(NAME) "9 4 - 6 2 + * 3 + 7 /"
		@echo "$(GREEN)Test 12:$(NC)"
		./$(NAME) "3 4 + 5000 1020 * * 3 /"
		@echo "$(GREEN)Test 13:$(NC)"
		./$(NAME) "1.3e-2 4.5e-3 + 3.2e-1 4.7e-2 - *"

.PHONY:all clean fclean re exe
##-----------------------------##
