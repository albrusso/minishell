/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:21:04 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/15 16:14:25 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cd_error(t_data *d, int i, char *s)
{
	if (i < 0)
		mini_error(d, 3, false);
	else if (i > 0)
		mini_error(d, 4, false);
	else if (i == 0)
		perror(s);
	return (1);
}

int	cd_setchange(t_data *d)
{
	free(d->oldpwd);
	d->oldpwd = ft_strdup(d->pwd);
	free(d->pwd);
	d->pwd = getcwd(NULL, 0);
	mini_setenv(d, "PWD", d->pwd);
	mini_setenv(d, "OLDPWD", d->oldpwd);
	return (0);
}

int	arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	mini_cd(t_data *d, char **cmd)
{
	int		ret;
	char	*tmp;

	tmp = mini_getenv(d->env, "HOME");
	if (cmd && arrlen(cmd) > 2)
		ret = cd_error(d, 42, NULL);
	else if (!tmp && !cmd[1])
		ret = cd_error(d, -42, NULL);
	else if (!cmd[1] && tmp)
	{
		ret = chdir(tmp);
		cd_setchange(d);
	}
	else
	{
		if (chdir(cmd[1]) == -1)
			ret = cd_error(d, 0, cmd[1]);
		else
			ret = cd_setchange(d);
	}
	return (ret);
}
