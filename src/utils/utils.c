/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:39:29 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/16 11:33:31 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**dup_arr(char **a)
{
	char	**tmp;
	int		i;

	i = 0;
	while (a[i])
		i++;
	tmp = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!tmp)
		return (NULL);
	i = 0;
	while (a[i])
	{
		tmp[i] = ft_strdup(a[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	free_arr(char **a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}

void	sortprint(char **a)
{
	int		len;
	char	**tmp;
	int		i;

	tmp = dup_arr(a);
	len = arrlen(tmp);
	i = -1;
	sort_string(tmp, len);
	while (tmp[++i])
	{
		if (ft_strncmp(tmp[i], "_", 1))
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putendl_fd(tmp[i], STDOUT_FILENO);
		}
	}
	free_arr(tmp);
}

void	swap_string(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_string(char **a, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strncmp(a[j], a[j + 1], ft_strlen(a[j + 1])) > 0)
				swap_string(&a[j], &a[j + 1]);
			j++;
		}
		i++;
	}
}
