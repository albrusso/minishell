/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:09:43 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/15 15:09:57 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**realloc_copy(char **arr, int size)
{
	char	**tmp;
	int		i;

	tmp = ft_calloc(size, sizeof(char *));
	i = -1;
	while (arr[++i])
		tmp[i] = ft_strdup(arr[i]);
	free_arr(arr);
	return (tmp);
}

char	**get_path(char **env)
{
	char	*tmp1;
	char	**tmp2;
	int		i;

	tmp1 = mini_getenv(env, "PATH");
	tmp2 = ft_split(tmp1, ':');
	i = -1;
	while (tmp2[++i])
		tmp2[i] = ft_strjoin_gnl(tmp2[i], "/");
	return (tmp2);
}

void	mini_setenv(t_data *d, const char *s1, char *s2)
{
	char	*tmp;
	int		i;

	i = -1;
	while (d->env[++i])
	{
		if (!ft_strncmp(d->env[i], s1, ft_strlen(s1)))
		{
			free(d->env[i]);
			tmp = ft_strjoin(s1, "=");
			d->env[i] = ft_strjoin_gnl(tmp, s2);
			return ;
		}
	}
	d->env = realloc_copy(d->env, i + 2);
	tmp = ft_strjoin(s1, "=");
	d->env[i] = ft_strjoin_gnl(tmp, s2);
	d->env[i + 1] = NULL;
	return ;
}

char	*mini_getenv(char **env, char *s)
{
	int	i[3];

	i[0] = 0;
	i[1] = ft_strlen(s);
	while (env[i[0]])
	{
		i[2] = ft_strlen(env[i[0]]);
		if (!ft_strncmp(env[i[0]], s, i[1]) && env[i[0]][i[1]] == '=')
			return (env[i[0]] + i[1] + 1);
		i[0]++;
	}
	return (NULL);
}
