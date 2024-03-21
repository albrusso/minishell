/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:00:16 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/21 14:40:26 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	ft_shell_init(t_mini *shell, char **envp)
{
	shell->simple_cmd = NULL;
	shell->lex = NULL;
	shell->pid = NULL;
	shell->heredoc = NULL;
	shell->reset = false;
	if (envp)
	{
		shell->env = ft_arrdup(envp);
		shell->pwd = getenv("PWD");
		shell->old_pwd = getenv("OLDPWD");
		shell->path = ft_pathdup(getenv("PATH"));
		shell->msg = ft_strjoin(getenv("USER"), "@minishell ");
	}
	return (0);
}
int	ft_restart_shell(t_mini *shell)
{
	free(shell->prompt);
	ft_shell_init(shell, NULL);
	ft_start_shell(shell);
	return (1);
}