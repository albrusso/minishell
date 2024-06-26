/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:46:58 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/16 12:45:21 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*try_expand_help(char *res, char *s, char **env, int sei[3])
{
	char	*tmp;
	int		j;

	tmp = ft_calloc(sei[1] - sei[0] + 1, 1);
	ft_memcpy(tmp, &s[sei[0]], sei[1] - sei[0]);
	j = -1;
	while (env[++j])
	{
		if (ft_strchr(env[j], '=')
			&& !ft_strncmp(env[j], tmp, ft_strlen(tmp))
			&& env[j][ft_strlen(tmp)] == '=')
		{
			res = ft_strjoin_gnl(res, ft_strchr(env[j], '=') + 1);
			sei[2] = sei[1] - 1;
			break ;
		}
	}
	if (res[0] == '\0')
		res = try_expander_copy(res, &s[sei[2]], &sei[2], sei[1]);
	free(tmp);
	return (res);
}

char	*try_expand_utils(char *res, char **env, char *s, int *i)
{
	int		sei[3];
	char	*tmp;

	sei[0] = *i + 1;
	sei[1] = sei[0];
	sei[2] = *i;
	while (s[sei[1]] && ft_isalnum(s[sei[1]]))
		++sei[1];
	if (sei[0] != sei[1])
	{
		tmp = ft_strdup(res);
		free(res);
		res = try_expand_help(tmp, s, env, sei);
	}
	else
		res = ft_strjoin_gnl(res, "$");
	*i = sei[2];
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
	bool	dquote;
	int		i;

	i = -1;
	dquote = false;
	res = ft_calloc(1, sizeof(char));
	while (s[++i])
	{
		if (s[i] == '"')
			dquote = !dquote;
		else if (s[i] == '\'' && !dquote)
			res = copy_insidequote(res, s, &i);
		else if (s[i] == '$')
		{
			if (s[i + 1] == '?')
				res = try_expand_g_exit(res, &i);
			else
				res = try_expand_utils(res, env, s, &i);
		}
		else
			res = copy_char(res, s, i);
	}
	return (res);
}

void	expander(t_data *d, t_lexer **lex)
{
	char	*tmp;
	t_lexer	*tmp1;

	tmp1 = *lex;
	if (ft_strchr(tmp1->s, '$'))
	{
		tmp = ft_strdup(tmp1->s);
		free(tmp1->s);
		tmp1->s = try_expand(d->env, tmp);
		if (!ft_strncmp(tmp1->s, tmp, ft_strlen(tmp)))
		{
			free(tmp1->s);
			tmp1->s = ft_strdup("");
		}
		free(tmp);
	}
	else
	{
		if (i_strchr(tmp1->s, '\'') < i_strchr(tmp1->s, '"'))
			tmp1->s = delete_and_replace(tmp1->s, '"', '\'');
		else
			tmp1->s = delete_and_replace(tmp1->s, '\'', '"');
	}
}
