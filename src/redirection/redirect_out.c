/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:07:54 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/11 12:38:30 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	open_output(t_parser *p, char *s)
{
	if (p->fd_out != -42)
		close(p->fd_out);
	p->fd_out = open(&s[2], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (p->fd_out < 0)
	{
		perror(&s[2]);
		g_exit = 1;
		p->exe = false;
	}
}

void	open_append(t_parser *p, char *s)
{
	if (p->fd_out != -42)
		close(p->fd_out);
	p->fd_out = open(&s[3], O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (p->fd_out < 0)
	{
		perror(&s[3]);
		g_exit = 1;
		p->exe = false;
	}
}
