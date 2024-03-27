/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:26:53 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/27 18:13:17 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lex_print(t_lexer **lex)
{
	t_lexer	*tmp;

	tmp = *lex;
	while(tmp->n)
	{
		printf("%s\n", tmp->s);
		tmp = tmp->n;
	}
}

void	lexer(t_data *d)
{
	char	**tmp;
	char	*tmp1;
	int		i;

	i = 0;
	tmp = ft_split(d->line, '|');
	while (tmp[i])
	{
		tmp1 = ft_strtrim(tmp[i], " ");
		free(tmp[i]);
		tmp[i] = ft_strdup(tmp1);
		lexadd_back(&d->lex, lexnew(ft_strdup(tmp[i])));
		if (tmp[i + 1])
			lexadd_back(&d->lex, lexnew(ft_strdup("|")));
		free(tmp1);
		i++;
	}
	lex_print(&d->lex);
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	t_lexer_free(&d->lex);
}
