/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:44:08 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/04 19:51:39 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lexnew(char *s1, t_token t)
{
	t_lexer		*new;
	static int	i = 0;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->s = s1;
	new->token = t;
	new->id = i;
	new->next = NULL;
	return (new);
}

t_lexer	*lexlast(t_lexer *lex)
{
	t_lexer	*tmp;

	if (lex)
	{
		tmp = lex;
		while (1)
		{
			if (!tmp->next)
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

void	lexadd_back(t_lexer **lex, t_lexer *new)
{
	t_lexer	*last;

	if (!lex || !*lex)
		*lex = new;
	else
	{
		last = lexlast(*lex);
		last->next = new;
	}
}