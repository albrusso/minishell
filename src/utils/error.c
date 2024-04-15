/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 11:26:00 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/15 13:37:25 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_synatx_token(t_data *d, char *s)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", STDERR_FILENO);
	if (!ft_strncmp(s, "|", 1))
		ft_putendl_fd("'|'", STDERR_FILENO);
	else if (!ft_strncmp(s, ">>", 2))
		ft_putendl_fd("'>>'", STDERR_FILENO);
	else if (!ft_strncmp(s, "<<", 2))
		ft_putendl_fd("'<<'", STDERR_FILENO);
	else if (!ft_strncmp(s, ">", 1))
		ft_putendl_fd("'>'", STDERR_FILENO);
	else if (!ft_strncmp(s, "<", 1))
		ft_putendl_fd("'<'", STDERR_FILENO);
}