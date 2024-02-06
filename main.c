/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:52:50 by albrusso          #+#    #+#             */
/*   Updated: 2024/02/06 16:26:39 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl_signal(int sig)
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
	return (*envp + 5);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	root;

	if (ac != 1 || av[1])
		return (0);
	root.path = ft_find_path(envp);
	root.cmd = ft_split(root.path, ':');
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_ctrl_signal);
	/*while (root.cmd[i])
	{
		printf("%s\n", root.cmd[i]);
		i++;
	}*/
	
	while (1)
	{
		root.rl_prompt = readline("Minishell v 7.1 >");
		add_history(root.rl_prompt);
		if (root.rl_prompt && ft_strncmp(root.rl_prompt, "exit", ft_strlen("exit")) == 0)
		{
			printf("exit\n");
			exit(0);
		}
	}
	return (0);
}
