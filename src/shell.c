/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:00:16 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/19 16:07:22 by albrusso         ###   ########.fr       */
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
	shell->env = ft_arrdup(envp);
	shell->pwd = getenv("PWD");
	shell->old_pwd = getenv("OLDPWD");
	//shell->path = ft_pathdup(getenv("PATH"));
	return (0);
}