/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:46:49 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/25 17:17:57 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchrindex(char *str, int i, char c)
{
	while (str[i])
	{
		if (str[i] == c)
			return (i);
	}
	return (0);
}

char	ft_expander(char *str, int *i, char **env)
{
	
	return (str);
}