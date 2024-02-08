/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:52:50 by albrusso          #+#    #+#             */
/*   Updated: 2024/02/08 16:18:56 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char	*ft_find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (ft_strdup(*envp + 5));
}

char	*ft_search_pwd(char **envp, const char *str)
{
	if (!ft_strncmp("old", str, 3))
	{
		while (ft_strncmp("OLDPWD", *envp, 6))
			envp++;
		return(ft_strdup(*envp + 7));
	}
	else if (!ft_strncmp("curr", str, 4))
	{
		while (ft_strncmp("PWD", *envp, 3))
			envp++;
		return(ft_strdup(*envp + 4));
	}
	else if (!ft_strncmp("home", str, 4))
	{
		while (ft_strncmp("HOME", *envp, 4))
			envp++;
		return(ft_strdup(*envp + 5));
	}
	return (NULL);
}

void	ft_init_root(t_shell *root, char **envp)
{
	root->env = ft_arrdup(envp);
	root->path = ft_find_path(envp);
	root->cmd = ft_split(root->path, ':');
	root->old_pwd = ft_search_pwd(envp, "old");
	root->curr_pwd = ft_search_pwd(envp, "curr");
	root->home_pwd = ft_search_pwd(envp, "home");
}

int	main(int ac, char **av, char **envp)
{
	t_shell	root;

	if (ac != 1 || av[1])
		return (0);
	ft_init_root(&root, envp);
	signal(SIGQUIT, ft_signal_handler);
	signal(SIGINT, ft_signal_handler);
	
	while (1)
	{
		root.rl_prompt = readline("Minishell v 7.1 > ");
		add_history(root.rl_prompt);
		if (root.rl_prompt && ft_strncmp(root.rl_prompt, "exit", ft_strlen("exit")) == 0)
		{
			printf("%s\n", root.old_pwd);
			printf("%s\n", root.curr_pwd);
			printf("exit\n");
			ft_clean_exit(&root);
			exit(0);
		}
		if (!ft_strncmp("cd", root.rl_prompt, 2))
		{
			if (ft_strlen(root.rl_prompt) > 3)
				ft_cd(*&root.rl_prompt + 3, &root);
			else
				ft_cd(NULL, &root);
		}
	}
	return (0);
}
