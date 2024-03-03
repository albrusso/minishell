/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:27:33 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/03 17:12:54 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*get_env(char **envp)
{
	int	i;
	t_list	*tmp;

	i = 1;
	if (envp[0])
	{
		tmp = ft_lstnew(ft_strdup(envp[i]));
		tmp = tmp->next;
	}
	while (envp[i])
	{
		ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	return (tmp);
}

char	**get_path(void)
{
	int		len;
	char	**path;
	char	**tmp;
	char	*s;
	
	s = getenv("PATH");
	if (!s)
		return (NULL);
	tmp = ft_split(s, ':');
	len = arrlen(tmp);
	path = (char **)ft_calloc(len + 1, sizeof(char *));
	len = -1;
	while (tmp[len++])
		path[len] = ft_strjoin(tmp[len], "/");
	len = -1;
	while (tmp[len++])
		free(tmp[len]);
	return (path);
}
