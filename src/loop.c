/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:02:34 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/21 14:57:22 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_mini *shell, int exitcode)
{
	free_arr(shell->path);
	free_arr(shell->env);
	free(shell->prompt);
	free(shell->msg);
	exit(exitcode);
}

int	ft_start_shell(t_mini *shell)
{
	char	*tmp;

	tmp = readline(shell->msg);
	shell->prompt = ft_strtrim(tmp, " ");
	free(tmp);
	if (!shell->prompt || !ft_strncmp(shell->prompt, "exit", 5))
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		ft_exit(shell, EXIT_SUCCESS);
	}
	if (shell->prompt[0] == '\0')
		return(ft_restart_shell(shell));
	add_history(shell->prompt);
	ft_restart_shell(shell);
	return (1);
}