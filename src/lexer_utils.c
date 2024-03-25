/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:34:08 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/25 13:13:33 by albrusso         ###   ########.fr       */
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
	if (!head_tmp)
		head_tmp = node;
	else
	{
		while (head_tmp->next)
			*lst = head_tmp->next;
		head_tmp->next = node;
	}
}

void	ft_lexclear(t_lexer **lst)
{
	while ((*lst)->next)
	{
		if ()
	}
		
}
