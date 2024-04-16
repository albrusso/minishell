/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:42:36 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/16 09:14:08 by albrusso         ###   ########.fr       */
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
# include <limits.h>

extern int	g_exit;

typedef struct s_message
{
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
	int				fd_in;
	int				fd_out;
	bool			exe;
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
	int			pid;
	int			end[2];
	bool		restart;
	t_lexer		*lex;
	t_parser	*pars;
	t_message	m;
}		t_data;

//utils
void		free_arr(char **a);
char		**dup_arr(char **a);

void		t_message_init(t_message *m, char **env);
char		*t_message_utils(t_message *m);
char		*relative_path(char *s1, char *s2);
void		t_message_free(t_message *m);

void		t_data_init(t_data *d, char **envp);
void		t_data_free(t_data *d, bool _exit);

void		signal_handler(int sig);
void		signal_print(int sig);

void		error_synatx_token(t_data *d, char *s);

char		*mini_getenv(char **env, char *s);
void		mini_setenv(t_data *d, const char *s1, char *s2);
char		**get_path(char **env);
char		**realloc_copy(char **arr, int size);

//lexer
void		t_lexer_free(t_lexer **lex);
void		lexadd_back(t_lexer **lex, t_lexer *new);
t_lexer		*lexlast(t_lexer *lex);
t_lexer		*lexnew(char *s);

int			find_nextquote(char *s, int i, int *quote, char c);
int			match_quote(char *s);

int			lexer(t_data *d);
int			check_lexer(t_data *d);
char		**parse_input(t_data *d);
void		lexhelp(t_data *d, char *s, char **a, int i[2]);

int			nospace(char *s);
char		*realloc_space(char *s, int len, int index);
void		lex_print(t_lexer **lex);

//expander
void		expander(t_data *d, t_lexer **lex);
char		*try_expand(char *env[], char *s);
char		*try_expand_g_exit(char *res, int *i);
char		*try_expand_utils(char *res, char **env, char *s, int *i);
char		*try_expander_copy(char *res, char *s, int *i, int end);

char		*copy_insidequote(char *res, char *s, int *i);
char		*copy_char(char *res, char *s, int i);
char		*delete_and_replace(char *s, char c1, char c2);
int			i_strchr(char *s, char c);

//parser
int			parslst_size(t_parser *lst);
void		t_parser_free(t_parser **pars);
void		parsadd_back(t_parser **pars, t_parser *new);
t_parser	*parslast(t_parser *pars);
t_parser	*parsnew(char **cmd, t_lexer *redir);

int			size_malloc(t_lexer *lex);
void		add_redir(t_data *d, t_lexer **redir, t_lexer *n1, t_lexer *n2);
int			is_redir(char *s);
void		fill_cmdredir(t_data *d, char **cmd, t_lexer *lex);
void		parser(t_data *d);

//redirection
void		close_redirect(t_parser *p);
void		set_piperedirect(t_data *d, t_parser *p);
void		set_redirect(t_parser *p);
void		open_redirect(t_data *d, t_parser *p);
int			is_redir(char *s);

void		open_heredoc(t_data *d, t_parser *p, char *s);
int			heredoc(t_data *d, char *s, int fd);
void		open_input(t_parser *p, char *s);

void		open_output(t_parser *p, char *s);
void		open_append(t_parser *p, char *s);

//executer
void		executer(t_data *d, t_parser *p);
void		try_execute(t_data *d, t_parser *p, char **cmd);
void		execute_onecmd(t_data *d, t_parser *p);

void		cmd_pipe(t_data *d, t_parser *p);
void		child_process(t_data *d, t_parser *p);
void		exec_builtin_fork(t_data *d, t_parser *p);
void		parent_process(t_data *d, t_parser *p);
void		wait_child(t_data *d);

//builtin
int			execute_builtin(t_data *d, t_parser *p, char **cmd);
int			is_builtin(char *s);

int			cd_error(t_data *d, int i, char *s);
int			cd_setchange(t_data *d);
int			arrlen(char **arr);
int			mini_cd(t_data *d, char **cmd);

int			mini_echo(char **cmd);

int			mini_env(t_data *d, char **env, char **path);

int			mini_exit(t_data *d, char **cmd);

char		*env_value(char *s, char *tmp1);
void		export_inenv(t_data *d, char *s);
int			mini_export(t_data *d, char **cmd);

int			mini_pwd(char *s);

int			mini_unset(t_data *d, char **cmd);
void		unset_env(t_data *d, char *s);

int			clean_exit(t_data *d, t_message *m, bool _exit);
int			mini_error(t_data *d, int err, bool b);
int			error_syntax_token(t_data *d, char *s);
int			lexindex(t_lexer **lex, t_lexer *node);

#endif