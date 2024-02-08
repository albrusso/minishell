/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:37:48 by albrusso          #+#    #+#             */
/*   Updated: 2024/02/08 16:27:09 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_arrdup(char **arr)
{
	int		i;
	char	**arr_dup;

	i = 0;
	while (arr[i])
		i++;
	arr_dup = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (arr[i])
	{
		arr_dup[i] = ft_strdup(arr[i]);
		i++;
	}
	arr_dup[i] = NULL;
	return(arr_dup);
}

void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}


void	ft_clean_exit(t_shell *root)
{
	ft_free_array(root->env);
	ft_free_array(root->cmd);
	free(root->old_pwd);
	free(root->curr_pwd);
	free(root->home_pwd);
	free(root->path);
	exit(0);
}