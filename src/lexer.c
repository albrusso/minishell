/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:07:18 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/25 17:42:45 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_iswhiespace(char c)
{
	if (c == ' ' || (c > 8 && c < 14))
		return (1);
	return (0);
}

int	ft_skipspace(char *str, int i)
{
	while (str[i])
	{
		if (!ft_iswhiespace(str[i]))
			break ;
		i++;
	}
	return (i);
}

t_tokens	ft_istoken(int token)
{
	static int	token_arr[3][2] = {
	{'|', PIPE},
	{'>', OUTPUT},
	{'<', INPUT},
	};
	int			i;

	i = 0;
	while (i < 3)
	{
		if (token_arr[i][0] == token)
			return (token_arr[i][1]);
		i++;
	}
	return (0);
}

int	ft_addtoken(t_lexer **lst, char *prompt, int i)
{
	if (ft_istoken(prompt[i]) == OUTPUT && ft_istoken(prompt[i + 1]) == OUTPUT)
	{
		ft_addnode(lst, ft_newnode(NULL, APPEND));
		return (i + 2);
	}
	else if (ft_istoken(prompt[i]) == INPUT && ft_istoken(prompt[i + 1]) == INPUT)
	{
		ft_addnode(lst, ft_newnode(NULL, HEREDOC));
		return (i + 2);
	}
	else
	{
		ft_addnode(lst, ft_newnode(NULL, ft_istoken(prompt[i])));
		return (i + 1);
	}
}

int	ft_addstr(t_lexer **lst, char *prompt, int i, char **env)
{
	int		j;
	char	*str;

	j = i;
	while (prompt[j] && !ft_istoken(prompt[j]) && !ft_iswhiespace(prompt[j]))
		j++;
	printf("j: %d\n", j);
	str = ft_substr(prompt, i, j);
	// if (ft_strchrindex(str, 0, '$'))
	// 	str = ft_expander(str, i, env);
	ft_addnode(lst, ft_newnode(ft_substr(prompt, i, j), 0));
	return (j);
}

void	ft_lexer(t_mini *shell_data)
{
	int	i;

	i = 0;
	while (shell_data->prompt[i])
	{
		i = ft_skipspace(shell_data->prompt, i);
		printf("i: %d\n", i);
		if (ft_istoken(shell_data->prompt[i]))
			i = ft_addtoken(&shell_data->lex, shell_data->prompt, i);
		else
			i = ft_addstr(&shell_data->lex, shell_data->prompt, i, shell_data->env);
	}
}