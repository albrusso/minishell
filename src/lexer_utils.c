/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:34:08 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/25 15:42:34 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*ft_newnode(char *str, t_tokens tok)
{
	t_lexer		*tmp;
	static int	i = 0;

	tmp = (t_lexer *) ft_calloc(1, sizeof(t_lexer));
	if (!tmp)
		return (NULL);
	tmp->s = str;
	tmp->token = tok;
	tmp->i = i++;
	tmp->prev = NULL;
	tmp->next = NULL;
	return (tmp);
}

void	ft_addnode(t_lexer **lst, t_lexer *node)
{

	t_lexer	*head_tmp;

	head_tmp = *lst;
	if (!(*lst))
		*lst = node;
	else
	{
		while (head_tmp->next)
			head_tmp = head_tmp->next;
		head_tmp->next = node;
		node->prev = head_tmp;
	}
}

void	ft_freenode(t_lexer	**node)
{
	if ((*node)->s)
		free((*node)->s);
	(*node)->s = NULL;
	free(*node);
	*node = NULL;
}

void	ft_lexclear_first(t_lexer **lst)
{
	t_lexer	*tmp;

	tmp = *lst;
	*lst = tmp->next;
	ft_freenode(&tmp);
	if (*lst)
		(*lst)->prev = NULL;
}

void	ft_lexclear_one(t_lexer **lst, int i)
{
	t_lexer	*head_tmp;
	t_lexer	*prev_tmp;
	t_lexer	*tmp;

	head_tmp = *lst;
	tmp = head_tmp;
	if ((*lst)->i == i)
		ft_lexclear_first(lst);
	else
	{
		while (tmp && tmp->i != i)
		{
			prev_tmp = tmp;
			tmp = tmp->next;
		}
		if (tmp)
			prev_tmp->next = tmp->next;
		else
			prev_tmp->next = NULL;
		if (prev_tmp->next)
			prev_tmp->next->prev = prev_tmp;
		ft_freenode(&tmp);
		*lst = head_tmp;
	}
}

void	ft_lexclear(t_lexer **lst)
{
	t_lexer	*tmp;

	if (!(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_freenode(lst);
		*lst = tmp;
	}
	*lst = NULL;
}
