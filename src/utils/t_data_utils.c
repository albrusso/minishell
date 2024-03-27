/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:04:43 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/27 17:24:43 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	t_data_free(t_data *d, bool _exit)
{
	if (_exit)
	{
		if (d->env)
			free_env(d->env);
		if (d->pwd)
			free(d->pwd);
		if (d->oldpwd)
		 	free(d->oldpwd);
		rl_clear_history();
		ft_putendl_fd("exit", STDOUT_FILENO);
	}
	if (d->line)
		free(d->line);
	d->line = NULL;
}

void	t_data_init(t_data *d, char **envp)
{
	d->env = dup_env(envp);
	d->pwd = mini_getenv(d->env, "PWD");
	d->oldpwd = mini_getenv(d->env, "OLDPWD");
	d->line = NULL;
}
