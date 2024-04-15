/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:30:43 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/15 16:15:57 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	mini_env(t_data *d, char **env, char **path)
{
	int	i;

	if (!path)
	{
		mini_error(d, 5, NULL);
		return (127);
	}
	i = -1;
	while (env[++i])
	{
		if (!ft_strchr(env[i], '='))
			i++;
		else
			printf("%s\n", env[i]);
	}
	return (0);
}
