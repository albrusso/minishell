/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:30:43 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/03 17:37:06 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	mini_env(char **env, char **path)
{
	int	i;

	if (!path)
	{
		mini_error("env: No such file or directory");
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