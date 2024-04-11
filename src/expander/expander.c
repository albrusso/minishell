/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:46:58 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/11 17:58:20 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*try_expander_copy(char *res, char *s, int *i, int end)
{
	char	*tmp;

	tmp = ft_calloc(end - (*i) + 1, sizeof(char));
	ft_memcpy(tmp, s, end - (*i));
	res = ft_strjoin_gnl(res, tmp);
	free(tmp);
	*i = end - 1;
	return (res);
}

char	*try_expand_utils(char *res, char **env, char *s, int *i)
{
	int		startend[2];
	int		j;
	char	*tmp;

	startend[0] = *i + 1;
	startend[1] = startend[0];
	while (s[startend[1]] && ft_isalnum(s[startend[1]]))
		++startend[1];
	if (startend[0] != startend[1])
	{
		tmp = ft_calloc(startend[1] - startend[0] + 1, 1);
		ft_memcpy(tmp, &s[startend[0]], startend[1] - startend[0] - 1);
		j = -1;
		while (env[++j])
		{
			if (ft_strchr(env[j], '=') && !ft_strncmp(env[j], tmp, ft_strlen(tmp)))
			{
				res = ft_strjoin_gnl(res, ft_strchr(env[j], '=') + 1);
				*i = startend[1] - 1;
				break ;
			}
		}
		if (res[0] == '\0')
			res = try_expander_copy(res, &s[*i], &*i, startend[1]);
		free(tmp);
	}
	else
		res = ft_strjoin_gnl(res, "$");
	return (res);
}

char	*try_expand_g_exit(char *res, int *i)
{
	char	*tmp;

	tmp = ft_itoa(g_exit);
	res = ft_strjoin_gnl(res, tmp);
	free(tmp);
	*i = *i + 1;
	return (res);
}

char	*try_expand(char *env[], char *s)
{
	char	*res;
	char	*tmp;
	bool	dquote;
	int		i;

	i = -1;
	dquote = false;
	res = ft_calloc(1, sizeof(char));
	while (s[++i])
	{
		if (s[i] == '"')
			dquote = !dquote;
		else if (s[i] == '\'' && dquote == false)
		{
			i++;
			while (s[i] && s[i] != '\'')
			{
				tmp = ft_calloc(2, 1);
				ft_strlcpy(tmp, &s[i], 1);
				res = ft_strjoin_gnl(res, tmp);
				free(tmp);
				i++;
			}
		}
		else if (s[i] == '$')
		{
			if (s[i + 1] == '?')
				res = try_expand_g_exit(res, &i);
			else
				res = try_expand_utils(res, env, s, &i);
		}
		else
		{
			tmp = ft_calloc(2, 1);
			ft_strlcpy(tmp, &s[i], 1);
			res = ft_strjoin_gnl(res, tmp);
			free(tmp);
		}
	}
	return (res);
}


void	expander(t_data *d, t_lexer **lex)
{
	t_lexer	*tmp;
	char	*tmp1;

	tmp = *lex;
	while (tmp)
	{
		if (ft_strchr(tmp->s, '$'))
		{
			tmp1 = ft_strdup(tmp->s);
			free(tmp->s);
			tmp->s = try_expand(d->env, tmp1);
			free(tmp1);
		}
		else
		{
			tmp1 = ft_strdup(tmp->s);
			free(tmp->s);
			tmp->s = ft_strtrim(tmp1, "\"");
			free(tmp1);
		}
		tmp = tmp->n;
	}
}
