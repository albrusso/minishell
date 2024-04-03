/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:34:36 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/03 15:09:52 by albrusso         ###   ########.fr       */
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
	while (tmp)
	{
		printf("+++ cmd +++\n");
		print_array(tmp->cmd);
		printf("+++ red +++\n");
		lex_print(&tmp->redir);
		printf("---- ----\n");
		tmp = tmp->n;
	}
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

void	add_redir(t_lexer **redir, char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, " ");
	tmp = ft_strjoin_gnl(tmp, s2);
	lexadd_back(redir, lexnew(ft_strdup(tmp)));
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
			lex = lex->n;
			break ;
		}
		else if (is_redir(lex->s))
		{
			add_redir(&redir, lex->s, lex->n->s);
			lex = lex->n;
		}
		else
			cmd[i++] = ft_strdup(lex->s);
		lex = lex->n;
	}
	cmd[i] = NULL;
	parsadd_back(&d->pars, parsnew(dup_env(cmd), redir));
	d->lex = lex;
	free_array(cmd);
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
		tmp = d->lex;
	}
	pars_print(&d->pars);
	d->lex = head;
}
