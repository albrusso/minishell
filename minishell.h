/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:43:05 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/25 18:36:32 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "mylib/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

extern int	g_exit;

#define ERR_ARGS "Minishell don't accept argument"

typedef enum s_tokens
{
	PIPE = 1,
	OUTPUT,
	APPEND,
	INPUT,
	HEREDOC,
}	t_tokens;

typedef struct s_lexer
{
	char			*s;
	t_tokens		token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_simple_cmd
{
	char					**s;
	//int						(*builtin)(t_mini *, struct s_simple_cmd *);
	int						num_redir;
	char					*heredoc_file;
	t_lexer					*redir;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmd;

typedef struct s_parser
{
	t_lexer			*lex;
	t_lexer			*redir;
	int				num_redir;
	struct s_mini	*shell;
}	t_parser;

typedef struct s_mini
{
	char					*prompt;
	char					*msg;
	char					**path;
	char					**env;
	t_simple_cmd			*simple_cmd;
	t_lexer					*lex;
	char					*pwd;
	char					*old_pwd;
}	t_mini;

void	ft_shell_init(t_mini *shell_data, char **envp);
void	ft_shell_signal(void);
void	ft_shell_loop(t_mini *shell_data);
void	ft_shell_exit(t_mini *shell_data);

t_lexer	*ft_newnode(char *str, t_tokens tok);
void	ft_addnode(t_lexer **lst, t_lexer *node);
void	ft_lexclear_one(t_lexer **lst, int i);
void	ft_lexclear_first(t_lexer **lst);
void	ft_freenode(t_lexer	**node);
void	ft_lexclear(t_lexer **lst);

void	ft_lexer(t_mini *shell_data);

char	*ft_expander(char *prompt, char **env);

int	ft_strchrindex(char *str, int i, char c);


int	ft_env(t_mini *shell_data);


#endif