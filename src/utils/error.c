/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 11:26:00 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/15 19:39:44 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	mini_error(t_data *d, int err, bool b)
{
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	if (err == 1)
		ft_putendl_fd("unexpected newline while looking for matching quote",
			STDOUT_FILENO);
	if (err == 2)
		ft_putendl_fd("exit: too many arguments", STDOUT_FILENO);
	if (err == 3)
		ft_putendl_fd("cd: HOME not set", STDOUT_FILENO);
	if (err == 4)
		ft_putendl_fd("cd: too many arguments", STDOUT_FILENO);
	if (err == 5)
		ft_putendl_fd("env: No such file or directory", STDOUT_FILENO);
	return (clean_exit(d, &d->m, b), 0);
}

int	error_syntax_token(t_data *d, char *s)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	if (!ft_strncmp(s, "|", 1))
		return (ft_putendl_fd("'|'", STDERR_FILENO), 0);
	else if (!ft_strncmp(s, ">>", 2))
		return (ft_putendl_fd("'>>'", STDERR_FILENO), 0);
	else if (!ft_strncmp(s, "<<", 2))
		return (ft_putendl_fd("'<<'", STDERR_FILENO), 0);
	else if (!ft_strncmp(s, ">", 1))
		return (ft_putendl_fd("'>'", STDERR_FILENO), 0);
	else if (!ft_strncmp(s, "<", 1))
		return (ft_putendl_fd("'<'", STDERR_FILENO), 0);
	(void)d;
	return (42);
}
