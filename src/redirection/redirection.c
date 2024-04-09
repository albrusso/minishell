/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:20:29 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/09 15:32:38 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	open_redirect(t_data *d, t_parser *p)
{
	t_lexer	*tmp;

	tmp = p->redir;
	while (tmp)
	{
		if (!ft_strncmp(tmp->s, ">>", 2))
			open_append(p, tmp->s);
		else if (!ft_strncmp(tmp->s, ">", 1))
			open_output(p, tmp->s);
		else if (!ft_strncmp(tmp->s, "<<", 2))
			open_heredoc(d, p, tmp->s);
		else if (!ft_strncmp(tmp->s, "<", 1))
			open_input(p, tmp->s);
		tmp = tmp->n;
	}	
}

void	set_redirect(t_parser *p)
{
	if (p->fd_in != -42)
	{
		close(STDIN_FILENO);
		dup2(p->fd_in, STDIN_FILENO);
		close(p->fd_in);
	}
	if (p->fd_out != -42)
	{
		close(STDOUT_FILENO);
		dup2(p->fd_out, STDOUT_FILENO);
		close(p->fd_out);
	}
}
