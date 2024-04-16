/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:57:42 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/16 15:50:21 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	wait_child(t_data *d)
{
	int	status;

	waitpid(d->pid, &status, 0);
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit = WTERMSIG(status) + 128;
}

void	parent_process(t_data *d, t_parser *p)
{
	signal(SIGINT, signal_parent);
	signal(SIGQUIT, signal_parent);
	if (p->exe == false && p->n)
	{
		close(d->end[1]);
		dup2(d->end[0], STDIN_FILENO);
		close(d->end[0]);
	}
	else if (p->exe == true && p->n)
	{
		close(d->end[1]);
		if (p->cmd[0])
		{
			dup2(d->end[0], STDIN_FILENO);
			close(d->end[0]);
		}
	}
	close_redirect(p);
	wait_child(d);
}

void	exec_builtin_fork(t_data *d, t_parser *p)
{
	g_exit = execute_builtin(d, p, p->cmd);
	clean_exit(d, &d->m, true);
}

void	child_process(t_data *d, t_parser *p)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (p->redir)
		open_redirect(d, p);
	if (p->exe == false)
	{
		close_redirect(p);
		if (p->n)
			close(d->end[0]);
		clean_exit(d, &d->m, true);
	}
	else if (p->n)
		set_piperedirect(d, p);
	else
		set_redirect(p);
	if (is_builtin(p->cmd[0]))
		exec_builtin_fork(d, p);
	else if (p->cmd && !p->cmd[0])
		clean_exit(d, &d->m, true);
	else if (p->exe == true)
		execute_onecmd(d, p);
}

void	cmd_pipe(t_data *d, t_parser *p)
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
