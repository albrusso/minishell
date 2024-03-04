/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:55:12 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/04 18:05:40 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_lst(t_list **lst)
{
	t_list *curr;
	t_list *next;

	if (!lst || !*lst)
		return;
	curr = *lst;
	while (curr) {
		next = curr->next;
		free(curr->content);
		free(curr);
		curr = next;
	}
	*lst = NULL;
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

