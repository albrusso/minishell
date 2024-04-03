/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:21:04 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/03 17:17:30 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cd_error(int i, char *s)
{
	if (i < 0)
		mini_error("cd: HOME not set");
	else if (i > 0)
		mini_error("cd: too many arguments");
	else if (i == 0)
		perror(s);
	return (1);
}

int	cd_setchange(t_data *d, char *s)
{
	free(d->oldpwd);
	d->oldpwd = ft_strdup(d->pwd);
	free(d->pwd);
	d->pwd = ft_strdup(s);
	mini_setenv(d->env, "PWD", d->pwd);
	mini_setenv(d->env, "OLDPWD", d->oldpwd);
	return (0);
}

int	mini_cd(t_data *d, char **cmd)
{
	int		ret;

	if (cmd[2])
		ret = cd_error(42, NULL);
	else if (!mini_getenv(d->env, "HOME") && !cmd[1])
		ret = cd_error(-42, NULL);
	else if (!cmd[1])
		ret = chdir(mini_getenv(d->env, "HOME"));
	else
	{
		if (chdir(cmd[1]) == -1)
			ret = cd_error(0, cmd[1]);
		else
			ret = cd_setchange(d, cmd[1]);
	}
	return (ret);
}
