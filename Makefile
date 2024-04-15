# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albrusso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 16:14:01 by albrusso          #+#    #+#              #
#    Updated: 2024/04/15 17:27:54 by albrusso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                  CONFIG                                      #
################################################################################

NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
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
			src/utils/error.c \
			src/utils/signal.c \
			src/utils/t_data_utils.c \
			src/utils/t_message_utils.c \
			src/utils/utils.c \
			src/redirection/redirection.c \
			src/redirection/redirect_in.c \
			src/redirection/redirect_out.c \
			src/parser/parser.c \
			src/parser/t_parser_utils.c \
			src/lexer/lexer.c \
			src/lexer/lexer_utils.c \
			src/lexer/t_lexer_utils.c \
			src/lexer/quotes.c \
			src/expander/expander.c \
			src/expander/expander_utils.c \
			src/executer/executer.c \
			src/executer/pipex.c \
			src/builtin/builtin.c \
			src/builtin/mini_cd.c \
			src/builtin/mini_echo.c \
			src/builtin/mini_env.c \
			src/builtin/mini_exit.c \
			src/builtin/mini_export.c \
			src/builtin/mini_pwd.c \
			src/builtin/mini_unset.c

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
	@mkdir -p $(OBJ_DIR)/src/parser
	@mkdir -p $(OBJ_DIR)/src/executer
	@mkdir -p $(OBJ_DIR)/src/builtin
	@mkdir -p $(OBJ_DIR)/src/redirection

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