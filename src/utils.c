/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:08:30 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/21 14:12:41 by albrusso         ###   ########.fr       */
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
	rtn = ft_calloc(sizeof(char *), i + 1);
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
	char	*tmp;
	char	**path;
	int		i;

	i = 0;
	path = ft_split(s, ':');
	while (path[i])
	{
		if (ft_strncmp(&path[i][ft_strlen(path[i]) - 1], "/", 1) != 0)
		{
			tmp = ft_strjoin(path[i], "/");
			free(path[i]);
			path[i] = tmp;
		}
		i++;
	}
	return (path);
}

void	free_arr(char **arr)
{
	int	i;
	
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_chrlast(char *s, char c)
{
	int	len;
	int	i;
	int	last;

	len = ft_strlen(s);
	i = 0;
	last = 0;
	while (i < len)
	{
		if (s[i] == c)
			last = i;
		i++;
	}
	return (last);
}