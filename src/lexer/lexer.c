/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:26:53 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/09 08:57:37 by albrusso         ###   ########.fr       */
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
	int		i;

	i = -1;
	tmp = ft_calloc(len + 2, sizeof(char));
	while (++i < len + 2)
	{
		if (i == index + 1)
			tmp[i] = ' ';
		else if (i > index + 1)
			tmp[i] = s[i + 1];
		else
			tmp[i] = s[i];
	}
	printf("%s\n", tmp);
	free(s);
	return (tmp);
}

int	nospace_token(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != ' ' && ((s[i] != '<' || s[i] != '>' || s[i] != '|') && s[i + 1]))
		{
			if (s[i + 1] == '<' || s[i + 1] == '>' || s[i + 1] == '|')
				return (i);
		}
	}
	return (0);
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

char	**parse_input(t_data *d, char *s)
{
	char	**tokens;
	int		quotes[2];
	int		i[2];
	int		n;

	i[0] = -1;
	i[1] = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (nospace_token(s) != 0)
		s = realloc_space(s, ft_strlen(s), nospace_token(s));
	n = ft_strlen(s);
	tokens = ft_calloc(n + 1, sizeof(char *));
	while (++i[0] <= n)
	{
		if ((s[i[0]] == ' ' || s[i[0]] == '\0') && !quotes[0] && !quotes[1])
			lexhelp(d, s, tokens, i);
		else if (s[i[0]] == '\'')
			quotes[0] = !quotes[0];
		else if (s[i[0]] == '\"')
			quotes[1] = !quotes[1];
	}	
	return (tokens);
}

void	lexer(t_data *d)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = parse_input(d, d->line);
	while (tmp[++i])
		lexadd_back(&d->lex, lexnew(ft_strdup(tmp[i])));
	expander(d, &d->lex);
	i = -1;
	while (tmp[++i])
		free(tmp[i]);
	//lex_print(&d->lex);
	free(tmp);
}
