/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:26:53 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/15 18:23:35 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	while (nospace(d->line) != -42)
		d->line = realloc_space(d->line, ft_strlen(d->line), nospace(d->line));
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

int	check_lexer(t_data *d)
{
	t_lexer	*tmp;
	int		ret;

	ret = -42;
	tmp = d->lex;
	while (tmp)
	{
		if ((tmp->s[0] == '|' && !tmp->n) || (tmp->n && tmp->n->s[0] == '|')
			|| (tmp->s[0] == '|' && !lexindex(&d->lex, tmp)))
			ret = error_syntax_token(d, "|");
		else if (is_redir(tmp->s) && ft_strlen(tmp->s) < 3)
			ret = error_syntax_token(d, tmp->s);
		if (!ret)
			return (ret);
		tmp = tmp->n;
	}
	return (ret);
}

int	lexer(t_data *d)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = parse_input(d);
	while (tmp[++i])
		lexadd_back(&d->lex, lexnew(ft_strdup(tmp[i])));
	free_arr(tmp);
	if (!check_lexer(d))
	{
		g_exit = 2;
		return (0);
	}
	expander(d, &d->lex);
	return (42);
}
