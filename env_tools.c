/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:53:19 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/04 18:04:59 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_env(char **envp)
{
	int	i;
	t_list *tmp;

	i = 0;
	tmp = NULL;
	while (envp[i])
	{
		ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	return (tmp);
}

char	**get_path(void)
{
	char	*tmp;
	char	*tmp1;
	char	**path;
	int		i;

	i = 0;
	tmp = getenv("PATH");
	if (!tmp)
		return (NULL);
	path = ft_split(tmp, ':');
	while (path[i])
	{
		tmp1 = ft_strdup(path[i]);
		free(path[i]);
		path[i] = ft_strjoin(tmp1, "/");
		free(tmp1);
		i++;
	}
	return (path);
}
