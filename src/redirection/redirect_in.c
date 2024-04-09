/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:12:55 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/09 15:28:16 by albrusso         ###   ########.fr       */
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
	}
}

int	heredoc(t_data *d, char *s)
{
	char	*line;
	char	*line_stop;
	int		fd;

	line_stop = ft_strjoin(s, "\n");
	line = get_next_line(d->in);
	fd = open("./", O_CREAT | O_WRONLY, O_TRUNC, 0666);
	if (fd < 0)
		perror("heredoc");
	while (line)
	{
		if (!ft_strncmp(line, line_stop, ft_strlen(line_stop)))
		{
			close(fd);
			free(line_stop);
			free(line);
			fd = open("./", O_RDONLY, 0666);
			return (fd);
		}
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(d->in);
	}
	return (-43);
}

void	open_heredoc(t_data *d, t_parser *p, char *s)
{
	if (p->fd_in != -42)
		close(p->fd_in);
	p->fd_in = heredoc(d, &s[4]);
	if (p->fd_in < 0)
	{
		perror(&s[4]);
		g_exit = 1;
	}
}
