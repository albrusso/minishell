/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:01:41 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/23 17:59:07 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit = 0;

void	ft_free_shell(t_mini *shell_data)
{
	int	i;

	i = -1;
	while (shell_data->env[++i])
		free(shell_data->env[i]);
	free(shell_data->env);
	shell_data->env = NULL;
	i = -1;
	while (shell_data->path[++i])
		free(shell_data->path[i]);
	free(shell_data->path);
	shell_data->path = NULL;
	free(shell_data->old_pwd);
	shell_data->old_pwd = NULL;
	free(shell_data->pwd);
	shell_data->pwd = NULL;
	free(shell_data->msg);
	shell_data->msg = NULL;
	free(shell_data->prompt);
	shell_data->prompt = NULL;
}

void	ft_shell_exit(t_mini *shell_data)
{
	ft_free_shell(shell_data);
	write(STDOUT_FILENO, "exit\n", 5);
	exit(g_exit);
}

int	main(int ac, char **av, char **envp)
{
	t_mini	shell_data;

	if (ac != 1 || av[1])
		return (0);
	ft_shell_init(&shell_data, envp);
	ft_shell_signal();
	ft_shell_loop(&shell_data);
	ft_free_shell(&shell_data);
	return (0);
}