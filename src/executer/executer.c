/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:16:10 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/09 16:14:01 by albrusso         ###   ########.fr       */
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

void	child1(t_data *d, t_parser *p)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (p->redir)
		open_redirect(d, p);
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
		child1(d, p);
	else
		child2(d, p);
}

void	executer(t_data *d, t_parser *p)
{
	int		fd[2];
	int		prev_fd = d->in;
	pid_t	pid;

	if (parslst_size(p) == 1 && is_builtin(p->cmd[0]))
	{
		open_redirect(d, p);
		set_redirect(p);
		execute_builtin(d, p, p->cmd);
		return ;
	}
	while (p)
	{
		open_redirect(d, p);
		set_redirect(p);
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		if ((pid = fork()) == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			close(fd[0]);
			if (prev_fd != STDIN_FILENO)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (p->n != NULL)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			execute_onecmd(d, p);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(fd[1]);
			if (p->n != NULL)
				prev_fd = fd[0];
			wait(NULL);
		}
		p = p->n;
	}
	dup2(d->in, STDIN_FILENO);
	dup2(d->out, STDOUT_FILENO);
}
