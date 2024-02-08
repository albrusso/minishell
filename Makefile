# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albrusso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 14:42:23 by albrusso          #+#    #+#              #
#    Updated: 2024/02/08 14:45:37 by albrusso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -g
SRC		=	main.c \
			builtins/cd.c \
			utils.c
LIBFT	=	libft/libft.a
OBJ		=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME): $(OBJ)
		@make -C libft
		@$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME) $(LIBFT)
		@printf "minishell compiled!\n"

clean:
		@make -C libft clean
		@rm -rf $(OBJ)
		@printf "minishell object files removed!\n"

fclean:
		@rm -rf $(OBJ)
		@printf "minishell object files removed!\n"
		@make -C libft fclean
		rm -f $(NAME)
		@printf "minishell executable removed!\n"

re: fclean all

.PHONY: all clean fclean re
