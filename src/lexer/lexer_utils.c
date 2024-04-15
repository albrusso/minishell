/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:03:13 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/15 17:29:59 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lex_print(t_lexer **lex)
{
	t_lexer	*tmp;

	tmp = *lex;
	if (!tmp)
		return ;
	while (tmp->n)
	{
		printf("%s\n", tmp->s);
		tmp = tmp->n;
	}
	printf("%s\n", tmp->s);
}

char	*realloc_space(char *s, int len, int index)
{
	char	*tmp;

	tmp = ft_calloc(len + 2, sizeof(char));
	ft_strlcpy(tmp, s, index + 1);
	tmp[index + 1] = ' ';
	ft_strlcpy(tmp + index + 2, s + index + 1, len);
	free(s);
	return (tmp);
}

int	is_redirect(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (42);
	return (0);
}

int	nospace(char *s)
{
	int	len;
	int	i;

	i = -1;
	len = ft_strlen(s);
	while (++i < len)
	{
		if (is_redirect(s[i]))
		{
			if (i > 0 && s[i - 1] != ' ' && !is_redirect(s[i - 1]))
				return (i - 1);
			if (s[i + 1] != ' ' && !is_redirect(s[i + 1]))
				return (i);
		}
	}
	return (-42);
}
