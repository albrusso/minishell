/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:52:05 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/05 09:59:25 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define S_QUOTE 39
# define D_QUOTE 34
# define DOLLAR_SIGN 36

typedef enum s_token
{
	PIPE = 1,
	OUTPUT,
	INPUT,
	APPEND,
	HEREDOC,
}		t_token;

typedef struct s_lexer
{
	char			*s;
	t_token			token;
	int				id;
	struct s_lexer	*next;
}		t_lexer;

typedef struct s_shell
{
	t_list	*env;
	char	**path;
	char	*prompt;
	t_lexer	*lex_list;
}		t_shell;

t_list	*get_env(char **envp);
char	**get_path(void);

void free_lst(t_list **lst);
void	free_array(char **arr);

void	start_loop(t_shell *d);
int	is_whitespace(char c);


t_lexer	*lexnew(char *s1, t_token t);
t_lexer	*lexlast(t_lexer *lex);
void	lexadd_back(t_lexer **lex, t_lexer *new);

void	lexer(t_shell *d);
int	handle_str(t_shell *d, char *s, int i);
int	handle_squote(char *s, int i);
int	handle_dquote(char *s, int i);
int	handle_token(t_shell *d, char *s, int i);
int	is_token(char c);


#endif