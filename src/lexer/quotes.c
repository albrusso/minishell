/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:26:57 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/16 11:00:49 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	match_quote(char *s)
{
	int		i;
	bool	quotes[2];

	i = -1;
	quotes[0] = false;
	quotes[1] = false;
	while (s[++i])
	{
		if (s[i] == '\'' && !quotes[1])
			quotes[0] = !quotes[0];
		else if (s[i] == '"' && !quotes[0])
			quotes[1] = !quotes[1];
	}
	if (quotes[0] || quotes[1])
		return (0);
	return (1);
}
