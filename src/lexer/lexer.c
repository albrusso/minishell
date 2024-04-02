/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:26:53 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/02 16:07:56 by albrusso         ###   ########.fr       */
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

char	**parse_input(char *s, int n)
{
	char	**tokens;
	int		quotes[2];
	int		j[2];
	int		i[2];

	i[0] = -1;
	i[1] = 0;
	j[0] = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	tokens = ft_calloc(n + 1, sizeof(char *));
	while (++i[0] <= n)
	{
		if ((s[i[0]] == ' ' || s[i[0]] == '\0') && !quotes[0] && !quotes[1])
		{
			j[1] = i[0] - j[0];
			if (j[1] > 0)
			{
				tokens[i[1]] = ft_calloc((j[1] + 1), sizeof(char));
				ft_strlcpy(tokens[i[1]], &s[j[0]], j[1]);
				i[1]++;
			}
			j[0] = i[0] + 1;
		}
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
	tmp = parse_input(d->line, ft_strlen(d->line));
	while (tmp[++i])
		lexadd_back(&d->lex, lexnew(ft_strdup(tmp[i])));
	//lex_print(&d->lex);
	expander(d, &d->lex);
	//lex_print(&d->lex);
	i = -1;
	while (tmp[++i])
		free(tmp[i]);
	free(tmp);
}
