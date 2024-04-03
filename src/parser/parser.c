/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:34:36 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/03 15:02:43 by albrusso         ###   ########.fr       */
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
		lex_print(&tmp->redir);
		printf("---- ----\n");
		tmp = tmp->n;
	}
	printf("+++ cmd +++\n");
	print_array(tmp->cmd);
	printf("+++ red +++\n");
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
		if (lex->s == '|')
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
	free_array(cmd);
	t_lexer_free(&redir);
}

void	parser(t_data *d)
{
	t_lexer	*tmp;
	char	**cmd;
	int		i;

	tmp = d->lex;
	i = size_malloc(tmp);
	cmd = ft_calloc(i + 1, sizeof(char *));
	fill_cmdredir(d, cmd, tmp);
	pars_print(&d->pars);
}
