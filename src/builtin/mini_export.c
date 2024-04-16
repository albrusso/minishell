/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:37:32 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/16 15:17:55 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*env_value(char *s, char *tmp1)
{
	char	*tmp2;
	int		i;

	i = 0;
	if (tmp1)
	{
		while (s[i] && s[i] != '=')
		{
			if (!ft_isalnum(s[i]))
				return (NULL);
			i++;
		}
		if (i == 0)
			i++;
		tmp2 = ft_substr(s, 0, i);
	}
	else
		tmp2 = ft_strdup(s);
	return (tmp2);
}

int	export_inenv(t_data *d, char *s)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	tmp1 = ft_strchr(s, '=');
	tmp2 = env_value(s, tmp1);
	if (!tmp2)
		return (0);
	i = -1;
	while (d->env[++i])
	{
		if (!ft_strncmp(d->env[i], tmp2,
				ft_strlen(d->env[i]) - ft_strlen(ft_strchr(d->env[i], '='))))
		{
			free(d->env[i]);
			if (!tmp1 && !ft_strchr(tmp2, '='))
				tmp2 = ft_strjoin_gnl(tmp2, "=");
			d->env[i] = ft_strjoin_gnl(tmp2, tmp1);
			return (1);
		}
	}
	d->env = realloc_copy(d->env, i + 2);
	d->env[i] = ft_strjoin(tmp2, tmp1);
	free(tmp2);
	return (1);
}

int	mini_export(t_data *d, char **cmd)
{
	int	i;

	i = -1;
	if (!cmd[1])
		sortprint(d->env);
	else
	{
		i = 0;
		while (cmd[++i])
		{
			if (!export_inenv(d, cmd[i]))
			{
				ft_putstr_fd("minishell : export: `", STDOUT_FILENO);
				ft_putstr_fd(cmd[i], STDOUT_FILENO);
				ft_putendl_fd("': not a valid identifier", STDOUT_FILENO);
			}
		}
	}
	return (0);
}
