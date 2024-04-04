/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:42:36 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/04 18:08:30 by albrusso         ###   ########.fr       */
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
# include <wait.h>
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
	bool			exec;
	t_lexer			*redir;
	struct s_parser	*n;
}		t_parser;

typedef struct s_data
{
	char		**env;
	char		**path;
	char		*pwd;
	char		*oldpwd;
	char		*line;
	int			in;
	int			out;
	int			exit;
	int			end[2];
	int			pid;
	t_lexer		*lex;
	t_parser	*pars;
}		t_data;

void	signal_handler(int sig);
void	signal_print(int sig);

void	fork_command(t_data *d, t_parser *p);
void	child_process(t_data *d, t_parser *p);
void	parent_process(t_data *d, t_parser *p);

void	parent_wait(t_data *d);
void	exec_builtin_fork(t_data *d, t_parser *p);
void	execvshell(t_data *d, t_parser *p);



void	t_data_init(t_data *d, char **envp);
void	t_data_free(t_data *d, bool _exit);

char	*mini_getenv(char **env, char *s);
void	mini_setenv(t_data *d, const char *s1, char *s2);
char	**dup_env(char **envp);
char	*relative_path(char *s1, char *s2);
void	free_env(char **env);
char	**realloc_copy(char **arr, int size);


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

int	mini_cd(t_data *d, char **cmd);
int	mini_echo(char **cmd);
int	mini_env(char **env, char **path);
int	mini_export(t_data *d, char **cmd);
int	mini_pwd(char *s);
int	mini_unset(t_data *d, char **cmd);
int	is_builtin(char *s);
int	execute_builtin(t_data *d, char **cmd);
void	mini_error(char *s);

void	shell_executor(t_data *d);


void	executor(t_data *d);


#endif