/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:37:32 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/03 18:11:19 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export_inenv(t_data *d, char *s)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	tmp1 = ft_strchr(s, '=');
	i = 0;
	if (tmp1)
	{
		while (s[i] && s[i] != '=')
			i++;
		tmp2 = ft_substr(s, 0, i);
	}
	else
		tmp2 = ft_strdup(s);
	i = -1;
	while (d->env[++i]);
	{
		if (!ft_strncmp(d->env[i], tmp2, ft_strlen(tmp2)))
		{
			free(d->env[i]);
		}
	}
}

int	mini_export(t_data *d, char **cmd)
{
	int	i;

	i = -1;
	if (!cmd[1])
	{
		while (d->env[++i])
			printf("declare -x %s\n", d->env[i]);
	}
	else
	{
		i = 0;
		while (cmd[++i])
			export_inenv(d, cmd[i]);
	}
	return (0);
}