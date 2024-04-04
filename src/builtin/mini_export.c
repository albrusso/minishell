/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:37:32 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/04 14:31:29 by albrusso         ###   ########.fr       */
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
	while (d->env[++i])
	{
		if (!ft_strncmp(d->env[i], tmp2, ft_strlen(tmp2)))
		{
			free(d->env[i]);
			if (tmp1)
				tmp2 = ft_strjoin_gnl(tmp2, "=");
			d->env[i] = ft_strjoin(tmp2, tmp1);
			return ;
		}
	}
	d->env = realloc_copy(d->env, i + 2);
	d->env[i] = ft_strjoin(tmp2, tmp1);
	d->env[i + 1] = NULL;
	free(tmp2);
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
