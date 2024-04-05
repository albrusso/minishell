/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:16:10 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/05 18:07:12 by albrusso         ###   ########.fr       */
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

void	try_execute(t_data *d, char **cmd)
{
	if (is_builtin(cmd[0]))
		execute_builtin(d, cmd);
	else
		execvp(cmd[0], cmd);
}

void executer(t_data *d, struct s_parser *cmds)
{
	int fd[2]; 
	int prev_fd = STDIN_FILENO;
	pid_t pid;
	
	while (cmds) 
	{
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
			if (cmds->n != NULL)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			execute_onecmd(d, cmds);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(fd[1]);
			if (cmds->n != NULL) {
				prev_fd = fd[0];
			}	
			wait(NULL);
		}
		cmds = cmds->n;
	}
}
