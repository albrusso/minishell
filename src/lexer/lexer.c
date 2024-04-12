/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:26:53 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/12 16:58:19 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lex_print(t_lexer **lex)
{
	t_lexer	*tmp;

	tmp = *lex;
	if (!tmp)
		return ;
	while (tmp->n)
	{
		printf("%s\n", tmp->s);
		tmp = tmp->n;
	}
	printf("%s\n", tmp->s);
}

char	*realloc_space(char *s, int len, int index)
{
	char	*tmp;

	tmp = ft_calloc(len + 2, sizeof(char));
	ft_strlcpy(tmp, s, index + 1);
	tmp[index + 1] = ' ';
	ft_strlcpy(tmp + index + 2, s + index + 1, len);
	free(s);
	return (tmp);
}

int	is_redirect(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (42);
	return (0);
}

int	nospace_token(char *s)
{
	int	len;
	int	i;

	i = -1;
	len = ft_strlen(s);
	while (++i < len)
	{
		if (is_redirect(s[i]))
		{
			if (i > 0 && s[i - 1] != ' ' && !is_redirect(s[i - 1]))
				return (i - 1);
			if (s[i + 1] != ' ' && !is_redirect(s[i + 1]))
				return (i);
		}
	}
	return (-42);
}

void	lexhelp(t_data *d, char *s, char **a, int i[2])
{
	static int	j[2];

	if (d->restart)
	{
		d->restart = !d->restart;
		j[0] = 0;
	}
	j[1] = i[0] - j[0];
	if (j[1] > 0)
	{
		a[i[1]] = ft_calloc((j[1] + 1), sizeof(char));
		ft_strlcpy(a[i[1]], &s[j[0]], j[1]);
		i[1]++;
	}
	j[0] = i[0] + 1;
}

char	**parse_input(t_data *d)
{
	char	**tokens;
	bool	quotes[2];
	int		i[2];
	int		n;

	i[0] = -1;
	i[1] = 0;
	quotes[0] = false;
	quotes[1] = false;
	while (nospace_token(d->line) != -42)
		d->line = realloc_space(d->line, ft_strlen(d->line), nospace_token(d->line));
	n = ft_strlen(d->line);
	tokens = ft_calloc(n + 1, sizeof(char *));
	while (++i[0] <= n)
	{
		if ((d->line[i[0]] == ' ' || d->line[i[0]] == '\0')
			&& !quotes[0] && !quotes[1])
			lexhelp(d, d->line, tokens, i);
		else if (d->line[i[0]] == '\'' && !quotes[1])
			quotes[0] = !quotes[0];
		else if (d->line[i[0]] == '\"')
			quotes[1] = !quotes[1];
	}
	return (tokens);
}

void	lexer(t_data *d)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = parse_input(d);
	while (tmp[++i])
		lexadd_back(&d->lex, lexnew(ft_strdup(tmp[i])));
	expander(d, &d->lex);
	i = -1;
	while (tmp[++i])
		free(tmp[i]);
	free(tmp);
}
