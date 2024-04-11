/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:16:10 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/11 13:47:48 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_foundcmd(t_parser *p)
{
	write(STDERR_FILENO, "Command not found: ", 20);
	if (p->cmd[0])
		write(STDERR_FILENO, p->cmd[0], ft_strlen(p->cmd[0]));
	else
		write(STDERR_FILENO, "\'\'", 3);
	write(STDERR_FILENO, "\n", 2);
}

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
		error_foundcmd(p);
		g_exit = 127;
		clean_exit(d, &d->m, true);
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
		clean_exit(d, &d->m, true);
	}
	else if (p->n)
		set_piperedirect(d, p);
	else
		set_redirect(p);
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
	t_parser *tmp;

	tmp = p;
	while (tmp)
	{
		if (tmp->n)
		{
			
			if (pipe(d->end) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		if (!tmp->n && is_builtin(tmp->cmd[0]))
			execute_builtin(d, tmp, tmp->cmd);
		else
			cmd_pipe(d, tmp);
		tmp = tmp->n;
	}
	dup2(d->in, STDIN_FILENO);
	dup2(d->out, STDOUT_FILENO);
}
