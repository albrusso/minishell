/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:01:41 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/22 16:27:32 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit = 0;

int	main(int ac, char **av, char **envp)
{
	t_mini	shell_data;

	if (ac != 1 || av[1])
		return (0);
	ft_shell_init(&shell_data, envp);
	//ft_shell_loop(&shell_data);
	return (0);
}