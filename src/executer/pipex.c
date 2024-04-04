/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:57:42 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/04 18:05:47 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parent_process(t_data *d, t_parser *p)
{
	signal(SIGINT, signal_print);
	signal(SIGQUIT, signal_print);
	if (p->exec == true && p->n)
	{
		close(d->end[1]);
		if (p->cmd[0])
		{
			dup2(d->end[0], STDIN_FILENO);
			close(d->end[0]);
		}
	}
	parent_wait(d);
}

void	child_process(t_data *d, t_parser *p)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(p->cmd[0]))
		exec_builtin_fork(d, p);
	else
		execvshell(d, p);
}

void	fork_command(t_data *d, t_parser *p)
{
	d->pid = fork();
	if (d->pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (d->pid == 0)
		child_process(d, p);
	else
		parent_process(d, p);
}