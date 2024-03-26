/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:07:18 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/25 18:57:09 by albrusso         ###   ########.fr       */
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
		return (2);
	}
	else if (ft_istoken(prompt[i]) == INPUT && ft_istoken(prompt[i + 1]) == INPUT)
	{
		ft_addnode(lst, ft_newnode(NULL, HEREDOC));
		return (2);
	}
	else
	{
		ft_addnode(lst, ft_newnode(NULL, ft_istoken(prompt[i])));
		return (1);
	}
}

int	ft_skipquotes(char *prompt, int i, char c)
{
	int	j;

	j = 0;
	if (prompt[i + j] == c)
	{
		j++;
		while (prompt[i + j] && prompt[i + j] != c)
			j++;
	}
	return (j);
}

int	ft_addstr(t_lexer **lst, char *prompt, int i, char **env)
{
	char	*str;
	int	j;

	j = 0;
	while (prompt[i + j] && !(ft_istoken(prompt[i + j])))
	{
		j += ft_skipquotes(prompt, i + j, '\'');
		j += ft_skipquotes(prompt, i + j, '\"');
		if (ft_iswhiespace(prompt[i + j]))
			break ;
		j++;
	}
	str = ft_substr(prompt, i, j);
	if (ft_strchrindex(str, 0, '$'))
		str = ft_expander(str, env);
	ft_addnode(lst, ft_newnode(ft_strdup(str), 0));
	free(str);
	return (j);
}

void	ft_lexer(t_mini *shell_data)
{
	int	i;

	i = 0;
	while (shell_data->prompt[i])
	{
		i = ft_skipspace(shell_data->prompt, i);
		if (ft_istoken(shell_data->prompt[i]))
			i += ft_addtoken(&shell_data->lex, shell_data->prompt, i);
		else
			i += ft_addstr(&shell_data->lex, shell_data->prompt, i, shell_data->env);
	}
}