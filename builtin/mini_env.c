/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:37:13 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/03 14:50:16 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_lst(t_list **lst)
{
	while ((*lst))
	{
		if (!(*lst)->next)
			break ;
		ft_putstr_fd((char *)(*lst)->content, STDIN_FILENO);
		*lst = (*lst)->next;
	}
	ft_putstr_fd((char *)(*lst)->content, STDIN_FILENO);
}

int	mini_env(t_list *env)
{
	print_lst(&env);
	return (0);
}