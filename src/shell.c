/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:06:29 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/22 16:28:20 by albrusso         ###   ########.fr       */
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
	i = 0;
	while (arr[i++])
		arr_tmp[i] = ft_strdup(arr[i]);
	return (arr_tmp);
}

char	**ft_pathdup(const char *str)
{
	int		i;
	char	**path_tmp;
	char	*str_tmp;

	str_tmp = NULL;
	i = 0;
	path_tmp = ft_split(str, ':');
	while (path_tmp[i++])
	{
		str_tmp = ft_strjoin(path_tmp[i], "/");
		free(path_tmp[i]);
		path_tmp[i] = str_tmp;
		free(str_tmp);
	}
	return (path_tmp);
}

void	sigint_handle(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_shell_signal()
{
	signal(SIGINT, sigint_handle);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_shell_env(t_mini *shell_data, char **envp)
{
	shell_data->env = ft_arrdup(envp);
	shell_data->path = ft_pathdup(getenv("PATH"));
}

void	ft_shell_init(t_mini *shell_data, char **envp)
{
	ft_shell_env(shell_data, envp);
	ft_shell_signal();
}