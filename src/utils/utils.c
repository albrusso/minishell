/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:39:29 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/15 14:40:53 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**dup_arr(char **a)
{
	char	**tmp;
	int		i;

	i = 0;
	while (a[i])
		i++;
	tmp = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!tmp)
		return (NULL);
	i = 0;
	while (a[i])
	{
		tmp[i] = ft_strdup(a[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	free_arr(char **a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}
