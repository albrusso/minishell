/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:34:36 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/16 11:44:28 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	size_malloc(t_lexer *lex)
{
	t_lexer	*tmp;
	int		i;

	tmp = lex;
	i = 1;
	while (tmp && ft_strncmp(tmp->s, "|", 1))
	{
		tmp = tmp->n;
		i++;
	}
	return (i);
}

void	add_redir(t_data *d, t_lexer **redir, t_lexer **n1, t_lexer *n2)
{
	char	*tmp;

	tmp = ft_strjoin((*n1)->s, " ");
	expander(d, &n2);
	tmp = ft_strjoin_gnl(tmp, n2->s);
	lexadd_back(redir, lexnew(ft_strdup(tmp)));
	*n1 = (*n1)->n;
	free(tmp);
}

void	fill_cmdredir(t_data *d, char **cmd, t_lexer *lex)
{
	int		i;
	t_lexer	*redir;

	i = 0;
	redir = NULL;
	while (lex)
	{
		if (!ft_strncmp(lex->s, "|", 1))
		{
			expander(d, &lex);
			lex = lex->n;
			break ;
		}
		else if (is_redir(lex->s))
			add_redir(d, &redir, &lex, lex->n);
		else
		{
			expander(d, &lex);
			cmd[i++] = ft_strdup(lex->s);
		}
		lex = lex->n;
	}
	parsadd_back(&d->pars, parsnew(cmd, redir));
	d->lex = lex;
}

void	parser(t_data *d)
{
	t_lexer	*tmp;
	t_lexer	*head;
	char	**cmd;
	int		i;

	head = d->lex;
	tmp = d->lex;
	while (tmp)
	{
		i = size_malloc(tmp);
		cmd = ft_calloc(i + 1, sizeof(char *));
		fill_cmdredir(d, cmd, tmp);
		free_arr(cmd);
		tmp = d->lex;
	}
	d->lex = head;
}
