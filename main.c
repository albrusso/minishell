/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:53:09 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/04 18:15:42 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_list **lst)
{
	while (*lst)
	{
		printf("%s\n", (char *)(*lst)->content);
		*lst = (*lst)->next;
	}
}

void	init_data(t_shell *d, char **envp)
{
	d->prompt = NULL;
	if (envp)
	{
		d->env = get_env(envp);
		d->path = get_path();
	}
}

int	is_whitespace(char c)
{
	if (c == ' ' || (c >= 8 && c <= 14))
		return (1);
	return (0);
}


int	skip_space(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[j])
	{
		if (!is_whitespace(s[j]))
			break ;
		i++;
		j++;
	}
	return (i);
}

void	start_loop(t_shell *d)
{
	char	*usr;
	char	*msg;
	char	*tmp;

	usr = getenv("USER");
	if (!usr)
		usr = ft_strdup("guest");
	msg = ft_strjoin(usr, "@minishell v3.7> ");
	tmp = readline(msg);
	d->prompt = ft_substr(tmp, skip_space(tmp), ft_strlen(tmp));
	if(d->prompt[0])
		add_history(d->prompt);
	init_data(d, NULL);
	start_loop(d);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	data;

	if (ac != 1 || av[1])
		return(ft_putendl_fd("minishell don't accept agruments!", STDIN_FILENO), 0);
	init_data(&data, envp);
	start_loop(&data);
	//print_list(&data.env);
	free_array(data.path);
	free_lst(&data.env);
	return (0);
}