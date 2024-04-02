/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:42:36 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/02 15:32:29 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "mylib/libft/libft.h"
# include "mylib/gnl/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

extern int g_exit;

typedef struct s_message
{
	char	*user;
	char	*dir;
	char	*msg;
}		t_message;

typedef struct s_lexer
{
	char			*s;
	struct s_lexer	*n;
}		t_lexer;

typedef struct s_parser
{
	char			**cmd;
	t_lexer			*redir;
	struct s_parser	*n;
}		t_parser;

typedef struct s_data
{
	char		**env;
	char		*pwd;
	char		*oldpwd;
	char		*line;
	t_lexer		*lex;
	t_parser	*pars;
}		t_data;

void	t_data_init(t_data *d, char **envp);
void	t_data_free(t_data *d, bool _exit);

char	*mini_getenv(char **env, char *s);
char	**dup_env(char **envp);
char	*relative_path(char *s1, char *s2);
void	free_env(char **env);

void	t_message_init(t_message *msg, char **env);
void	t_message_free(t_message *m);

void	t_lexer_free(t_lexer **lex);
void	lexadd_back(t_lexer **lex, t_lexer *new);
t_lexer	*lexlast(t_lexer *lex);
t_lexer	*lexnew(char *s);

void	lexer(t_data *d);
void	lex_print(t_lexer **lex);


void	expander(t_data *d, t_lexer **lex);

void	free_array(char **arr);

void	parser(t_data *d);

t_parser	*parsnew(char **cmd, t_lexer *redir);
t_parser	*parslast(t_parser *pars);
void	parsadd_back(t_parser **pars, t_parser *new);
void	t_parser_free(t_parser **pars);



#endif