/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:33:22 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/25 18:36:58 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_mini *shell_data)
{
	int	i;

	i = 0;
	while (shell_data->env[i])
	{
		if (ft_strchrindex(shell_data->env[i], 0, '='))
			ft_putendl_fd(shell_data->env[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

