/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:07:18 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/25 13:12:36 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lexer(t_mini *shell_data)
{
	t_lexer	*node;
	t_lexer	*node1;
	t_lexer	*node2;

	node = ft_newnode(ft_strdup(shell_data->prompt), 0);
	ft_addnode(&shell_data->lex, node);
	node1 = ft_newnode(ft_strdup("ciao"), 0);
	ft_addnode(&shell_data->lex, node1);

	ft_lexclear_one(&shell_data->lex, 1);
	// ft_lexclear_one(&shell_data->lex, 1);
}