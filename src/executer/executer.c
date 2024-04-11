/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:16:10 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/10 13:35:41 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_onecmd(t_data *d, t_parser *p)
{
	char	*tmp;
	int		i;

	i = -1;
	if (is_builtin(p->cmd[0]))
		execute_builtin(d, p, p->cmd);
	else
	{
		if (!access(p->cmd[0], F_OK))
			execve(p->cmd[0], p->cmd, d->env);
		else
		{
			while (d->path[++i])
			{
				tmp = ft_strjoin(d->path[i], p->cmd[0]);
				if (!access(tmp, F_OK))
					execve(tmp, p->cmd, d->env);
				free(tmp);
			}
		}
	}
}

void	try_execute(t_data *d, t_parser *p, char **cmd)
{
	if (is_builtin(cmd[0]))
		execute_builtin(d, p, cmd);
	else
		execvp(cmd[0], cmd);
}

void	wait_child(t_data *d)
{
	int	status;
	waitpid(d->pid, &status, 0);
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit = WTERMSIG(status) + 128;
}

void	child2(t_data *d, t_parser *p)
{
	close(d->end[1]);
	if (p->cmd[0])
	{
		dup2(d->end[0], STDIN_FILENO);
		close(d->end[0]);
	}
	close_redirect(p);
	wait_child(d);
}

void	child1(t_data *d, t_parser *p)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (p->redir)
		open_redirect(d, p);
	if (p->n)
		set_piperedirect(d, p);
	else
		set_redirect(p);
	if (is_builtin(p->cmd[0]))
		g_exit = execute_builtin(d, p, p->cmd);
	else
		execute_onecmd(d, p);
	
}


void	parent_process(t_data *d, t_parser *p)
{
	signal(SIGINT, signal_print);
	signal(SIGQUIT, signal_print);
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
	clean_exit(d, NULL, true);
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
		clean_exit(d, NULL, true);
	}
	else if (p->n)
		set_piperedirect(d, p);
	else
		open_redirect(d, p);
	if (is_builtin(p->cmd[0]))
		exec_builtin_fork(d, p);
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

void	executer(t_data *d, t_parser *p)
{
	if (parslst_size(p) == 1 && is_builtin(p->cmd[0]))
	{
		open_redirect(d, p);
		set_redirect(p);
		execute_builtin(d, p, p->cmd);
		return ;
	}
	while (p)
	{
		if (pipe(d->end) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		cmd_pipe(d, p);
		p = p->n;
	}
}
