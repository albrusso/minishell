/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:15:22 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/16 10:46:55 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(char *s)
{
	if (!ft_strncmp(s, "cd", ft_strlen(s)))
		return (1);
	else if (!ft_strncmp(s, "echo", ft_strlen(s)))
		return (1);
	else if (!ft_strncmp(s, "env", ft_strlen(s)))
		return (1);
	else if (!ft_strncmp(s, "exit", ft_strlen(s)))
		return (1);
	else if (!ft_strncmp(s, "export", ft_strlen(s)))
		return (1);
	else if (!ft_strncmp(s, "pwd", ft_strlen(s)))
		return (1);
	else if (!ft_strncmp(s, "unset", ft_strlen(s)))
		return (1);
	return (0);
}

int	execute_builtin(t_data *d, t_parser *p, char **cmd)
{
	open_redirect(d, p);
	set_redirect(p);
	if (!ft_strncmp(cmd[0], "cd", 2))
		return (mini_cd(d, cmd));
	else if (!ft_strncmp(cmd[0], "echo", 4))
		return (mini_echo(cmd));
	else if (!ft_strncmp(cmd[0], "env", 3))
		return (mini_env(d, d->env, d->path));
	else if (!ft_strncmp(cmd[0], "exit", 4))
		return (mini_exit(d, cmd));
	else if (!ft_strncmp(cmd[0], "export", 6))
		return (mini_export(d, cmd));
	else if (!ft_strncmp(cmd[0], "pwd", 3))
		return (mini_pwd(d->pwd));
	else if (!ft_strncmp(cmd[0], "unset", 5))
		return (mini_unset(d, cmd));
	return (0);
}
