# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albrusso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/03 16:01:48 by albrusso          #+#    #+#              #
#    Updated: 2024/03/03 17:15:15 by albrusso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
LIBFT	=	libft/libft.a
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -g
RFLAGS	=	-L/opt/homebrew/opt/readline/lib -lreadline
RM		=	rm -f
SRC		=	main.c \
			utils/init.c \
			utils/utils.c \
			utils/env_utils.c
OBJ		=	$(SRC:.c=.o)

all:		$(NAME)
$(NAME):	$(OBJ)
			@make -sC libft
			@$(CC) $(CFLAGS) $(RFLAGS) $(LIBFT) $(OBJ) -o $(NAME)

clean:
			@make clean -sC libft
			@$(RM) $(OBJ)

fclean:		clean
			@$(RM) $(LIBFT)
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re