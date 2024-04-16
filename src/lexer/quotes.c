/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:26:57 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/15 19:27:14 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_nextquote(char *s, int i, int *quote, char c)
{
	int	j;

	j = i + 1;
	*quote += 1;
	while (s[j] && s[j] != c)
		j++;
	if (s[j] == c)
		*quote += 1;
	return (j - i + 1);
}

int	match_quote(char *s)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] == '\'')
		{
			while (i++ < ft_strlen(s))
			{
				if (s[i] == '\'')
					break ;
			}
			if (s[i] != '\'')
				return (0);
		}
		if (s[i] == '"')
		{
			while (i++ < ft_strlen(s))
			{
				if (s[i] == '"')
					break ;
			}
			if (s[i] != '"')
				return (0);
		}
		i++;
	}
	return (42);
}
