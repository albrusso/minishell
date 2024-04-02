/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_parser_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:30:34 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/02 16:03:13 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_parser	*parsnew(char **cmd, t_lexer *redir)
{
	t_parser	*new;

	new = (t_parser *)malloc(sizeof(t_parser));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->redir = NULL;
	if (redir)
		new->redir = redir;
	new->n = NULL;
	return (new);
}

t_parser	*parslast(t_parser *pars)
{
	t_parser	*tmp;

	if (pars)
	{
		tmp = pars;
		while (1)
		{
			if (!tmp->n)
				return (tmp);
			tmp = tmp->n;
		}
	}
	return (NULL);
}

void	parsadd_back(t_parser **pars, t_parser *new)
{
	t_parser	*last;

	if (pars)
	{
		if (*pars)
		{
			last = parslast(*pars);
			last->n = new;
		}
		else
			*pars = new;
	}
}

void	t_parser_free(t_parser **pars)
{
	t_parser	*tmp;

	if (pars)
	{
		while (*pars)
		{
			tmp = *pars;
			*pars = (*pars)->n;
			if (tmp->cmd)
				free_array(tmp->cmd);
			if (tmp->redir)
				t_lexer_free(&tmp->redir);
			free(tmp);
		}
		*pars = NULL;
	}
}