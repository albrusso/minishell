/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:27:33 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/16 08:34:39 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_lexer	*lexnew(char *s)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->s = s;
	new->n = NULL;
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
			if (!tmp->n)
				return (tmp);
			tmp = tmp->n;
		}
	}
	return (NULL);
}

void	lexadd_back(t_lexer **lex, t_lexer *new)
{
	t_lexer	*last;

	if (lex)
	{
		if (*lex)
		{
			last = lexlast(*lex);
			last->n = new;
		}
		else
			*lex = new;
	}
}

void	t_lexer_free(t_lexer **lex)
{
	t_lexer	*tmp;

	if (lex)
	{
		while (*lex)
		{
			tmp = *lex;
			*lex = (*lex)->n;
			if (tmp->s)
				free(tmp->s);
			free(tmp);
		}
		*lex = NULL;
	}
}

int	lexindex(t_lexer **lex, t_lexer *node)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = *lex;
	while (tmp)
	{
		if (tmp == node)
			return (i);
		i++;
		tmp = tmp->n;
	}
	return (-1);
}
