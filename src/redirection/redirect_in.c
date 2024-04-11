/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:12:55 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/11 17:36:22 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	open_input(t_parser *p, char *s)
{
	if (p->fd_in != -42)
		close(p->fd_in);
	p->fd_in = open(&s[3], O_RDONLY);
	if (p->fd_in < 0)
	{
		perror(&s[3]);
		g_exit = 1;
		p->exe = false;
	}
}

int	heredoc(t_data *d, char *s)
{
	char	*line;
	char	*line_stop;
	int		fd;

	line_stop = ft_strjoin(s, "\n");
	fd = open("heredoc", O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd < 0)
		perror("heredoc");
	while (1)
	{
		line = get_next_line(d->in);
		if (!line)
			return (fd);
		if (!ft_strncmp(line, line_stop, ft_strlen(line_stop)))
		{
			close(fd);
			free(line_stop);
			free(line);
			fd = open("heredoc", O_RDONLY, 0777);
			if (fd < 0)
				perror("heredoc");
			return (fd);
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	return (-43);
}

void	open_heredoc(t_data *d, t_parser *p, char *s)
{
	if (p->fd_in != -42)
		close(p->fd_in);
	p->fd_in = heredoc(d, &s[3]);
	if (p->fd_in < 0)
	{
		perror(&s[3]);
		g_exit = 1;
		p->exe = false;
	}
}
