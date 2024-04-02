/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:34:36 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/02 16:12:31 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		printf("%s\n", arr[i]);
}

void	pars_print(t_parser **pars)
{
	t_parser	*tmp;

	tmp = *pars;
	while (tmp->n)
	{
		printf("+++ cmd +++\n");
		print_array(tmp->cmd);
		printf("+++ red +++\n");
		if (tmp->redir)
			lex_print(&tmp->redir);
		printf("---- ----\n");
		tmp = tmp->n;
	}
	printf("+++ cmd +++\n");
	print_array(tmp->cmd);
	printf("+++ red +++\n");
	if (tmp->redir)
		lex_print(&tmp->redir);
	printf("---- ----\n");
}

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

void	add_redir(t_lexer *redir, char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, " ");
	tmp = ft_strjoin_gnl(tmp, s2);
	printf("%s\n", tmp);
	lexadd_back(&redir, lexnew(ft_strdup(tmp)));
	free(tmp);
}

int	is_redir(char *s)
{
	if (!ft_strncmp(s, "<", 1))
		return (1);
	if (!ft_strncmp(s, "<<", 2))
		return (1);
	if (!ft_strncmp(s, ">", 1))
		return (1);
	if (!ft_strncmp(s, ">>", 2))
		return (1);
	return (0);
}

void	fill_cmdredir(t_data *d, t_parser *par, t_lexer *lex)
{
	int	i;

	i = 0;
	while (lex)
	{
		if (is_redir(lex->s))
		{
			add_redir(par->redir, lex->s, lex->n->s);
			lex = lex->n;
		}
		else
		{
			par->cmd[i] = ft_strdup(lex->s);
			i++;
		}
		lex = lex->n;
	}
	par->cmd[i] = NULL;
	lex_print(&par->redir);
	parsadd_back(&d->pars, par);
}

void	parser(t_data *d)
{
	t_lexer	*tmp;
	t_lexer	*redir;
	t_parser	par;
	char	**cmd;
	int		i;


	redir = NULL;
	tmp = d->lex;
	i = size_malloc(tmp);
	par.redir = NULL;
	par.n = NULL;
	par.cmd = ft_calloc(i + 1, sizeof(char *));
	fill_cmdredir(d, &par, tmp);
	pars_print(&d->pars);
}