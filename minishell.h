/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:53:57 by albrusso          #+#    #+#             */
/*   Updated: 2024/02/06 13:16:43 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_shell
{
	char	*rl_prompt;
	char	**envp;
	char	**path;
	t_lexer	*all_lexer;
	char	*curr_pwd;
	char	*old_pwd;
	int		nbr_pipe;
}	t_shell;

typedef enum s_tokens
{
	PIPE,
	LESS,
	LESS_2,
	GREATER,
	GREATER_2
}	t_tokens;

typedef struct s_lexer
{
	char		*prompt_word;
	t_tokens	*token;
	int			i;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;

#endif