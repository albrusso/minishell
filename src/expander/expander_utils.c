/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:05:45 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/15 17:56:24 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*copy_char(char *res, char *s, int i)
{
	char	*tmp;

	tmp = ft_calloc(2, sizeof(char));
	ft_strlcpy(tmp, &s[i], 1);
	res = ft_strjoin_gnl(res, tmp);
	free(tmp);
	return (res);
}

char	*copy_insidequote(char *res, char *s, int *i)
{
	*i = *i + 1;
	while (s[*i] && s[*i] != '\'')
	{
		res = copy_char(res, s, *i);
		*i = *i + 1;
	}
	return (res);
}

char	*delete_and_replace(char *s, char c1, char c2)
{
	int		len;
	int		ij[2];
	bool	quote;
	char	*result;

	quote = false;
	len = ft_strlen(s);
	result = (char *)ft_calloc(len + 1, sizeof(char));
	ij[0] = -1;
	ij[1] = 0;
	while (s[++ij[0]])
	{
		if (s[ij[0]] == c2)
			quote = !quote;
		else if ((s[ij[0]] == c1 && quote) || s[ij[0]] != c1)
		{
			result[ij[1]] = s[ij[0]];
			ij[1]++;
		}
	}
	free(s);
	return (result);
}

int	i_strchr(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	return (INT_MAX);
}

char	*try_expander_copy(char *res, char *s, int *i, int end)
{
	char	*tmp;

	tmp = ft_calloc(end - (*i) + 1, sizeof(char));
	ft_memcpy(tmp, s, end - (*i));
	res = ft_strjoin_gnl(res, tmp);
	free(tmp);
	*i = end - 1;
	return (res);
}
