/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:05:45 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/12 16:57:09 by albrusso         ###   ########.fr       */
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
