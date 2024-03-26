/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:46:49 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/25 19:03:14 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchrindex(char *str, int i, char c)
{
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*delete_quotes(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], ft_strlen(str) - i);
		}
		i++;
	}
	return (str);
}

char	*ft_expander(char *str, char **env)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	if (!ft_strchrindex(str, 0, '\''))
		str = delete_quotes(str, '\"');
	tmp = ft_strdup(str);
	free(str);
	str = ft_strtrim(tmp, "$");
	free(tmp);
	tmp = NULL;
	len = ft_strlen(str);
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, len))
		{
			free(str);
			str = ft_substr(env[i], len + 1, ft_strlen(env[i]));
		}
		i++;
	}
	return (str);
}