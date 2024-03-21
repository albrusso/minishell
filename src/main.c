/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:55:12 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/21 14:46:50 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig)
{
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

int	main(int ac, char **av, char **envp)
{
	t_mini	shell;

	if (ac != 1 || av[1])
	{
		ft_putendl_fd("No argument request!", STDOUT_FILENO);
		exit(0);
	}
	ft_shell_init(&shell, envp);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	ft_start_shell(&shell);
	free_arr(shell.path);
	free_arr(shell.env);
	return (0);
}