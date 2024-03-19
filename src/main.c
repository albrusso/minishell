/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:55:12 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/19 16:29:38 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_mini	shell;

	if (ac != 1 || av[1])
	{
		ft_putendl_fd("No argument request!", STDOUT_FILENO);
		exit(0);
	}
	ft_shell_init(&shell, envp);
	return (0);
}