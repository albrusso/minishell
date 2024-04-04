/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:15:22 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/04 17:39:41 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	mini_error(char *s)
{
	printf("minishell: %s\n", s);
}

int	is_builtin(char *s)
{
	if (!ft_strncmp(s, "cd", 2))
		return (1);
	else if (!ft_strncmp(s, "echo", 4))
		return (1);
	else if (!ft_strncmp(s, "env", 3))
		return (1);
	else if (!ft_strncmp(s, "export", 6))
		return (1);
	else if (!ft_strncmp(s, "pwd", 3))
		return (1);
	else if (!ft_strncmp(s, "unset", 5))
		return (1);
	return (0);
}

int	execute_builtin(t_data *d, char **cmd)
{
	if (!ft_strncmp(cmd[0], "cd", 2))
		return(mini_cd(d, cmd));
	else if (!ft_strncmp(cmd[0], "echo", 4))
		return(mini_echo(cmd));
	else if (!ft_strncmp(cmd[0], "env", 3))
		return(mini_env(d->env, d->path));
	else if (!ft_strncmp(cmd[0], "export", 6))
		return(mini_export(d, cmd));
	else if (!ft_strncmp(cmd[0], "pwd", 3))
		return(mini_pwd(d->pwd));
	else if (!ft_strncmp(cmd[0], "unset", 5))
		return(mini_unset(d, cmd));
	return (0);
}