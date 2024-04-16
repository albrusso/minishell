/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:16:10 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/16 15:52:58 by albrusso         ###   ########.fr       */
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
			while (d->path && d->path[++i])
			{
				tmp = ft_strjoin(d->path[i], p->cmd[0]);
				if (!access(tmp, F_OK))
					execve(tmp, p->cmd, d->env);
				free(tmp);
			}
		}
		error_foundcmd(p);
		p->exe = false;
		g_exit = 127;
		clean_exit(d, &d->m, true);
	}
}

void	executer(t_data *d, t_parser *p)
{
	t_parser	*tmp;

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
