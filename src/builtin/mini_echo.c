/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:17:38 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/08 14:41:18 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	mini_echo(char **cmd)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	if (cmd[1] && !ft_strncmp(cmd[1], "-n", 2))
	{
		flag = true;
		i++;
	}
	while (cmd[++i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	return (0);
}
