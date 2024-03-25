/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:06:29 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/23 17:48:45 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_arrdup(char **arr)
{
	int		i;
	char	**arr_tmp;

	i = 0;
	while (arr[i])
		i++;
	arr_tmp = ft_calloc(i + 1, sizeof(char *));
	if (!arr_tmp)
		return (NULL);
	i = -1;
	while (arr[++i])
		arr_tmp[i] = ft_strdup(arr[i]);
	return (arr_tmp);
}

char	**ft_pathdup(const char *str)
{
	int		i;
	char	**path_tmp;
	char	*str_tmp;

	str_tmp = NULL;
	i = -1;
	path_tmp = ft_split(str, ':');
	while (path_tmp[++i])
	{
		str_tmp = ft_strjoin(path_tmp[i], "/");
		free(path_tmp[i]);
		path_tmp[i] = ft_strdup(str_tmp);
		free(str_tmp);
	}
	return (path_tmp);
}

void	ft_shell_env(t_mini *shell_data, char **envp)
{
	shell_data->env = ft_arrdup(envp);
	shell_data->path = ft_pathdup(getenv("PATH"));
	shell_data->msg = ft_strjoin(getenv("USER"), "@minishell ");
	shell_data->pwd = ft_strdup(getenv("PWD"));
	shell_data->old_pwd = ft_strdup(getenv("OLDPWD"));
}

void	ft_shell_init(t_mini *shell_data, char **envp)
{
	if (envp)
		ft_shell_env(shell_data, envp);
	shell_data->lex = NULL;
	shell_data->prompt = NULL;
	shell_data->simple_cmd = NULL;
}
