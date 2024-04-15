/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:10:23 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/15 17:13:51 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	mini_exit(t_data *d, char **cmd)
{
	if (arrlen(cmd) > 2)
		mini_error(d, 2, false);
	if (cmd[1])
		g_exit = ft_atoi(cmd[1]);
	else
		g_exit = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	return (clean_exit(d, &d->m, true));
}
