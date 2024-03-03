/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:40:37 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/03 17:18:53 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	print_lst(t_list **lst)
{
	while ((*lst))
	{
		if (!(*lst)->next)
			break ;
		ft_putendl_fd((char *)(*lst)->content, STDIN_FILENO);
		*lst = (*lst)->next;
	}
	ft_putendl_fd((char *)(*lst)->content, STDIN_FILENO);
}

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_putendl_fd(arr[i], STDIN_FILENO);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*usr;
	//char	*msg;

	if (ac != 1 || av[1])
		return(ft_putstr_fd("minishell don't accept argument\n", STDIN_FILENO), 0);
	init_data(&data, envp);
	usr = getenv("USER");
	if (!usr)
		usr = ft_strdup("guest");
	// while (1)
	// {
	// 	data.prompt = readline(msg = ft_strjoin(usr, "@minishell v3.7> "));
	// }
	print_lst(&data.env);
	print_arr(data.path);
	return (0);
}
