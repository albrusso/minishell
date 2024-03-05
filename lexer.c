/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:43:53 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/05 16:03:54 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token(char c)
{
	static int	token_table[3][2] = {
	{'|', PIPE},
	{'>', OUTPUT},
	{'<', INPUT},
	};
	int			i;

	i = 0;
	while (i < 3)
	{
		if (token_table[i][0] == c)
			return (token_table[i][1]);
		i++;
	}
	return (0);

}

int	handle_token(t_shell *d, char *s, int i)
{
	if (is_token(s[i]) == OUTPUT && (s[i + 1] && s[i + 1] == OUTPUT))
	{
		lexadd_back(&d->lex_list, lexnew(NULL, APPEND));
		return (2);
	}
	else if (is_token(s[i]) == INPUT && (s[i + 1] && s[i + 1] == INPUT))
	{
		lexadd_back(&d->lex_list, lexnew(NULL, HEREDOC));
		return (2);
	}
	else if (is_token(s[i]))
	{
		lexadd_back(&d->lex_list, lexnew(NULL, is_token(s[i])));
		return (1);
	}
	return (0);
}

int	handle_dquote(char *s, int i)
{
	int	j;

	j = 0;
	if (s[i + j] == D_QUOTE)
	{
		j++;
		while (s[i + j] && s[i + j] != D_QUOTE)
		{
			// if (s[i + j] == DOLLAR_SIGN && expand == 1)
			// 	expander();
			if (s[i + j] == S_QUOTE)
				j += handle_squote(s, i + j);
			j++;
		}
		j++;
	}
	return (j);
}

int	handle_squote(char *s, int i)
{
	int	j;

	j = 0;
	if (s[i + j] == S_QUOTE)
	{
		j++;
		while (s[i + j] && s[i + j] != S_QUOTE)
		{
			if (s[i + j] == D_QUOTE)
				j += handle_dquote(s, i + j);
			j++;
		}
		j++;
	}
	return (j);
}

int	handle_str(t_shell *d, char *s, int i)
{
	int	j;
	char	*tmp;

	j = 0;
	while (s[i + j] && !is_token(s[i + j]))
	{
		j += handle_squote(s, i + j);
		j += handle_dquote(s, i + j);
		// if (s[i + j] == DOLLAR_SIGN)
		// 	expander(s, i + j);
		if (is_whitespace(s[i + j]))
			break ;
		j++;
	}
	tmp = ft_substr(s, i, j);
	if (tmp[0] && tmp[0] == '\'')
		tmp = ft_strtrim(tmp, "\'");
	else
		tmp = ft_strtrim(tmp, "\"");
	lexadd_back(&d->lex_list, lexnew(tmp, 0));
	return (j);
}

void	matched_quotes(char *s, int *i, int *j, char c)
{
	*j += 1;
	*i += 1;
	while (s[*i] && s[*i] != c)
		*i += 1;
	if (s[*i] == c)
		*j += 1;
}

int	unmatched_quotes(char *s)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	while (s[i])
	{
		if (s[i] == S_QUOTE)
			matched_quotes(s, &i, &s_quote, S_QUOTE);
		if (s[i] == D_QUOTE)
			matched_quotes(s, &i, &d_quote, D_QUOTE);
		i++;
	}
	if (d_quote % 2 == 0 && s_quote % 2 == 0)
		return (0);
	else
		return (1);
}

void	print_lexer(t_lexer *lst)
{
	t_lexer	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("String:	%s\n", tmp->s);
		printf("Token:	%d\n", tmp->token);
		printf("Index:	%d\n", tmp->id);
		tmp = tmp->next;
	}
	
}

void	lexer(t_shell *d)
{
	int	i;
	int	read;

	i = 0;
	if (unmatched_quotes(d->prompt))
		return ;
	while (d->prompt[i])
	{
		read = 0;
		if (is_token(d->prompt[i]))
			read = handle_token(d, d->prompt, i);
		else
			read = handle_str(d, d->prompt, i);
		i += read;
		i++;
	}
	//print_lexer(d->lex_list);
}