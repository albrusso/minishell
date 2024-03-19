/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:08:30 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/19 16:28:53 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_arrdup(char **arr)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		rtn[i] = strdup(arr[i]);
		// if (rtn[i] == NULL)
		// {
		// 	free_arr(rtn);
		// 	return (rtn);
		// }
		i++;
	}
	return (rtn);
}

char	**ft_pathdup(char *s)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(s, ':');
	free(s);
	while (tmp[i])
	{
		if (ft_strncmp(&tmp[i][ft_strlen(tmp[i]) - 1], "/", 1) != 0)
			tmp[i] = ft_strjoin(tmp[i], "/");
		i++;
	}
	return (tmp);
}