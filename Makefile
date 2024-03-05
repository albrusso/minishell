# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albrusso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/04 16:58:48 by albrusso          #+#    #+#              #
#    Updated: 2024/03/05 09:41:59 by albrusso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                  CONFIG                                      #
################################################################################

NAME	=	minishell
CC		=	cc
LIBFT	=	libft/libft.a
CFLAGS	=	-Wall -Werror -Wextra
RM		=	rm -f

################################################################################
#                                  COLORS                                      #
################################################################################

GREEN	=	\033[38;5;76m
RED		=	\033[38;5;160m
YELLOW	=	\033[38;5;226m
ORANGE	=	\033[38;5;202m
PURPLE	=	\033[38;5;213m
LBLUE	=	\033[38;5;51m
BLUE	=	\033[38;5;117m
INDI	=	\033[38;5;99m
RESET	=	\033[00m

################################################################################
#                                   FILES                                      #
################################################################################

SRC		=	main.c \
			env_tools.c \
			free_tools.c \
			lexer.c \
			lexer_tools.c

OBJ		=	$(SRC:.c=.o)

################################################################################
#                                   MAKE                                       #
################################################################################

all:		$(NAME)

$(NAME):	$(OBJ)
			@make -sC libft
			@$(CC) $(CFLAGS) $(OBJ) -L/opt/homebrew/opt/readline/lib -o $(NAME) $(LIBFT) -lreadline
			@echo "$(BLUE)minishell $(GREEN)compiled!$(RESET)"

clean:
			@make clean -sC libft
			@ $(RM) $(OBJ)
			@echo "$(BLUE)minishell objects file $(YELLOW)removed!$(RESET)"

fclean:		clean
			@$(RM) $(LIBFT)
			@echo "$(BLUE)libft.a $(YELLOW)removed!$(RESET)"
			@$(RM) $(NAME)
			@echo "$(BLUE)minishell $(YELLOW)removed!$(RESET)"

re:			fclean all

PHONY:		all clean fclean re

.SILENT: