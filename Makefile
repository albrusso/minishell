# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albrusso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 16:14:01 by albrusso          #+#    #+#              #
#    Updated: 2024/03/28 14:54:06 by albrusso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                  CONFIG                                      #
################################################################################

NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Wextra
MYLIB	=	./mylib/libftprintfgnl.a
OBJ_DIR	=	.obj
SIZE	=	40

################################################################################
#                                  COLORS                                      #
################################################################################

RED		=	\033[1;31m
YELLOW	=	\033[1;33m
BLUE	=	\033[1;34m
GREEN	=	\033[1;32m
WHITE	=	\033[1;37m
DEFAULT	=	\033[0m

################################################################################
#                                   FILES                                      #
################################################################################

SRC		=	src/main.c \
			src/utils/env_utils.c \
			src/utils/t_data_utils.c \
			src/utils/t_message_utils.c \
			src/lexer/lexer_utils.c \
			src/lexer/t_lexer_utils.c \
			src/lexer/lexer.c \
			src/expander/expander.c

OBJ		=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

################################################################################
#                                   MAKE                                       #
################################################################################

all:	$(NAME)
$(NAME): $(OBJ)
	@make -sC mylib
	@$(CC) $(CFLAGS) -lreadline $(OBJ) -o $(NAME) $(MYLIB)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@printf "$(WHITE)%s$(BLUE)%-$(SIZE)s$(GREEN)%s$(DEFAULT)\n" "Compiling... " "$<" "[OK]"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/src
	@mkdir -p $(OBJ_DIR)/src/utils
	@mkdir -p $(OBJ_DIR)/src/lexer
	@mkdir -p $(OBJ_DIR)/src/expander

clean:
	@make clean -sC mylib
	@for file in $(OBJ); do \
		printf "$(WHITE)%s$(YELLOW)%-$(SIZE)s$(GREEN)%s$(DEFAULT)\n" "Removing...  " "$$file" "[OK]"; \
	done
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "$(WHITE)%s$(RED)%-$(SIZE)s$(GREEN)%s$(DEFAULT)\n" "Removing...  " "libftprintfgnl" "[OK]"
	@printf "$(WHITE)%s$(RED)%-$(SIZE)s$(GREEN)%s$(DEFAULT)\n" "Removing...  " "$(NAME)" "[OK]"
	@rm -f $(MYLIB)
	@rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

mem: $(NAME)
		valgrind --leak-check=full --show-leak-kinds=all --suppressions=./readline.supp ./$(NAME)

.PHONY: all clean fclean re run mem