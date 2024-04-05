/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:09:43 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/05 14:20:12 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	**dup_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (env);
}

char	*relative_path(char *s1, char *s2)
{
	char	*s3;
	char	*s4;

	if (!s1 || !s2)
		return (NULL);
	if (!ft_strncmp(s1, s2, ft_strlen(s1)))
		s3 = ft_strdup(s2 + ft_strlen(s1) + 1);
	else
		s3 = ft_strdup(s2);
	if (!ft_strncmp(s3, s1, ft_strlen(s1)))
		s4 = ft_strjoin("~", NULL);
	else
		s4 = ft_strjoin("~", s3);
	free(s3);
	return (s4);
}

char	**realloc_copy(char **arr, int size)
{
	char	**tmp;
	int		i;
	
	tmp = ft_calloc(size, sizeof(char *));
	i = -1;
	while (arr[++i])
		tmp[i] = ft_strdup(arr[i]);
	free_array(arr);
	return (tmp);
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
