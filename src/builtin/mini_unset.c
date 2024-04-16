/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:58:44 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/16 10:43:25 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	unset_env(t_data *d, char *s)
{
	int	i;
	int	j;

	i = -1;
	while (d->env[++i])
	{
		if (!ft_strncmp(d->env[i], s, ft_strlen(s)))
		{
			free(d->env[i]);
			j = i - 1;
			while (d->env[++j])
				d->env[j] = d->env[j + 1];
			return ;
		}
	}
}

int	mini_unset(t_data *d, char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (cmd[++i])
	{
		if (!ft_strchr(cmd[i], '='))
		{
			if (!ft_strncmp(cmd[i], "PATH", 4))
			{
				while (d->path[++j])
					free(d->path[j]);
				free(d->path);
				d->path = NULL;
			}
			unset_env(d, cmd[i]);
		}
		else
			printf("minishell: unset: '%s': not a valid identifier\n", cmd[i]);
	}
	return (0);
}
