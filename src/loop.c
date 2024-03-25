/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:33:28 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/25 17:45:17 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lexprint(t_lexer **lst)
{
	t_lexer	*tmp;

	if (!(*lst))
		return ;
	tmp = *lst;
	while (tmp->next)
	{
		printf("String: %s\nToken: %d\nIndex: %d\n", tmp->s, tmp->token, tmp->i);
		tmp = tmp->next;
	}
	printf("String: %s\nToken: %d\nIndex: %d\n", tmp->s, tmp->token, tmp->i);
}

void	ft_shell_clear(t_mini *shell_data)
{
	free(shell_data->prompt);
	ft_lexclear(&shell_data->lex);
	ft_shell_init(shell_data, NULL);
	ft_shell_loop(shell_data);
}

void	ft_shell_loop(t_mini *shell_data)
{
	char	*tmp;

	tmp = readline(shell_data->msg);
	shell_data->prompt = ft_strtrim(tmp, " ");
	free(tmp);
	tmp = NULL;
	if (!shell_data->prompt || !ft_strncmp(shell_data->prompt, "exit", 4))
		ft_shell_exit(shell_data);
	if (shell_data->prompt[0] == '\0')
		ft_shell_clear(shell_data);
	else
	{
		add_history(shell_data->prompt);
		ft_lexer(shell_data);
		ft_lexprint(&shell_data->lex);
		ft_shell_clear(shell_data);
	}
}