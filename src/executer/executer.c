/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:16:10 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/04 18:05:42 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_onecmd(t_data *d, t_parser *p)
{
	char	*tmp;
	int		i;

	i = -1;
	if (is_builtin(p->cmd[0]))
		execute_builtin(d, p->cmd);
	else
	{
		if (!access(p->cmd[0], F_OK))
			execve(p->cmd[0], p->cmd, d->env);
		else
		{
			while (d->path[++i])
			{
				//printf("%s\n", d->path[i]);
				tmp = ft_strjoin(d->path[i], p->cmd[0]);
				if (!access(tmp, F_OK))
					execve(tmp, p->cmd, d->env);
				free(tmp);
			}
			
		}
	}
}

void	command_notfound(t_parser *p)
{
	write(STDERR_FILENO, "Command not found: ", 20);
	if (p->cmd[0])
		write(STDERR_FILENO, p->cmd[0], ft_strlen(p->cmd[0]));
	else
		write(STDERR_FILENO, "\'\'", 3);
	write(STDERR_FILENO, "\n", 2);
}

void	exec1(t_data *d, t_parser *p)
{
	if (p->cmd[0] == NULL)
		return ;
	if (access(p->cmd[0], F_OK) == 0)
	{
		execve(p->cmd[0], p->cmd, d->env);
		perror("execve1");
		exit(126);
	}
}

void	exec2(char *cmd_path, t_parser *tmp, t_parser *p, t_data *d)
{
	if (p->cmd[0] == NULL)
		return ;
	if (access(cmd_path, F_OK) == 0)
	{
		execve(cmd_path, tmp->cmd, d->env);
		perror("execve2");
		exit(126);
	}
}

void	execvshell(t_data *d, t_parser *p)
{
	int		i;
	int		j;
	char	*cmd_path;
	t_parser	*tmp;

	i = 0;
	j = 0;
	exec1(d, p);
	tmp = p;
	while (tmp->cmd[i] && d->path)
	{
		while (d->path[j])
		{
			cmd_path = ft_strjoin(d->path[j], tmp->cmd[i]);
			exec2(cmd_path, tmp, p, d);
			free(cmd_path);
			j++;
		}
		j = 0;
		i++;
	}
	command_notfound(p);
	exit(127);
}

void	exec_builtin_fork(t_data *d, t_parser *p)
{
	g_exit = execute_builtin(d, p->cmd);
	d->exit = g_exit;
}

void	parent_wait(t_data *d)
{
	int	status;

	waitpid(d->pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_exit = WEXITSTATUS(status);
		d->exit = g_exit;
	}
	else if (WIFSIGNALED(status))
	{
		g_exit = WTERMSIG(status) + 128;
		d->exit = g_exit;
	}
}

void	executor(t_data *d)
{
	t_parser	*p;

	p = d->pars;
	while (p)
	{
		d->exit = 0;
		if (p->n)
		{
			if (pipe(d->end) < 0)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		if (!p->n && is_builtin(p->cmd[0]))
		{
			g_exit = execute_builtin(d, p->cmd);
			d->exit = g_exit;
		}
		else if (d->exit == 0)
			fork_command(d, p);
		p = p->n;
	}
	dup2(d->in, STDIN_FILENO);
	dup2(d->out, STDOUT_FILENO);
}

// void	executor(t_data *d)
// {
// 	t_parser	*p;
// 	//int			dup[2];

// 	p = d->pars;
// 	while (p)
// 	{
// 		// if (p->n)
// 		// {
// 		// 	if (pipe(dup) < 0)
// 		// 		exit(EXIT_FAILURE);
// 		// }
// 		if (!p->n)
// 			execute_onecmd(d, p);
// 		// else
// 		// 	execute_fork(d, p);
// 		p = p->n;
// 	}
// }