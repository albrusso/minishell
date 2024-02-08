/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:53:57 by albrusso          #+#    #+#             */
/*   Updated: 2024/02/08 15:45:02 by albrusso         ###   ########.fr       */
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
# include <signal.h>
# include "libft/libft.h"

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
	char			*prompt_word;
	t_tokens		*token;
	int				i;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_shell
{
	char	*rl_prompt;
	char	**env;
	char	**cmd;
	char	*path;
	t_lexer	*all_lexer;
	char	*curr_pwd;
	char	*old_pwd;
	char	*home_pwd;
	int		nbr_pipe;
}	t_shell;

int	ft_cd(const char *path, t_shell *root);
char	*ft_search_pwd(char **envp, const char *str);

char	**ft_arrdup(char **arr);
void	ft_free_array(char **arr);
void	ft_clean_exit(t_shell *root);

#endif