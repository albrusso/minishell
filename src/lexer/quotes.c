/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:26:57 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/15 17:31:38 by albrusso         ###   ########.fr       */
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
	int	i;
	int	quotes[2];

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			i += find_nextquote(s, i, &quotes[0], '\'');
		else if (s[i] == '"')
			i += find_nextquote(s, i, &quotes[1], '"');
		if (s[i] == '\0')
			break ;
		else
			i++;
	}
	if (quotes[0] % 2 || quotes[1] % 2)
		return (0);
	return (42);
}
