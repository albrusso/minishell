/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_message_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:57:41 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/08 14:52:06 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	t_message_free(t_message *m)
{
	if (m->dir)
		free(m->dir);
	if (m->msg)
		free(m->msg);
}

char	*message(t_message *m)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin("minishell:", m->dir);
	s2 = ft_strjoin(s1, " ");
	free(s1);
	return (s2);
}

void	t_message_init(t_message *m, char **env)
{
	m->dir = relative_path(mini_getenv(env, "HOME"), mini_getenv(env, "PWD"));
	m->msg = message(m);
}
