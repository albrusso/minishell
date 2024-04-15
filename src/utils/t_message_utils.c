/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_message_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:57:41 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/15 17:59:22 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	t_message_free(t_message *m)
{
	if (m->dir)
		free(m->dir);
	if (m->msg)
		free(m->msg);
	m->dir = NULL;
	m->msg = NULL;
}

char	*t_message_utils(t_message *m)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin("minishell:", m->dir);
	s2 = ft_strjoin(s1, " ");
	free(s1);
	return (s2);
}

char	*relative_path(char *s1, char *s2)
{
	char	*s3;
	char	*s4;

	if (!s1 || !s2)
		return (NULL);
	if (!ft_strncmp(s1, s2, ft_strlen(s1)))
		s3 = ft_substr(s2, ft_strlen(s1), ft_strlen(s2));
	else
		s3 = ft_strdup(s2);
	if (!ft_strncmp(s3, s1, ft_strlen(s3)))
		s4 = ft_strjoin("~", NULL);
	else
		s4 = ft_strjoin("~", s3);
	free(s3);
	return (s4);
}

void	t_message_init(t_message *m, char **env)
{
	m->dir = relative_path(mini_getenv(env, "HOME"), mini_getenv(env, "PWD"));
	m->msg = t_message_utils(m);
}
