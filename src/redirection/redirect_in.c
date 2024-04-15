/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:12:55 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/15 17:48:25 by albrusso         ###   ########.fr       */
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

int	heredoc(t_data *d, char *s, int fd)
{
	char	*line[2];

	line[1] = ft_strjoin(s, "\n");
	fd = open("heredoc", O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd < 0)
		perror("heredoc");
	while (1)
	{
		line[0] = get_next_line(d->in);
		if (!line[0])
			return (fd);
		if (!ft_strncmp(line[0], line[1], ft_strlen(line[1])))
		{
			close(fd);
			free(line[1]);
			free(line[0]);
			fd = open("heredoc", O_RDONLY, 0777);
			if (fd < 0)
				perror("heredoc");
			return (fd);
		}
		ft_putstr_fd(line[0], fd);
		free(line[0]);
	}
	return (-43);
}

void	open_heredoc(t_data *d, t_parser *p, char *s)
{
	int	fd;

	fd = -42;
	if (p->fd_in != -42)
		close(p->fd_in);
	p->fd_in = heredoc(d, &s[3], fd);
	if (p->fd_in < 0)
	{
		perror(&s[3]);
		g_exit = 1;
		p->exe = false;
	}
}
