/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:04:43 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/04 17:25:37 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	t_data_free(t_data *d, bool _exit)
{
	if (_exit)
	{
		if (d->env)
			free_env(d->env);
		if (d->path)
			free_array(d->path);
		if (d->pwd)
			free(d->pwd);
		if (d->oldpwd)
		 	free(d->oldpwd);
		rl_clear_history();
		ft_putendl_fd("exit", STDOUT_FILENO);
	}
	if (d->line)
		free(d->line);
	d->line = NULL;
	if (d->lex)
		t_lexer_free(&d->lex);
	if (d->pars)
		t_parser_free(&d->pars);
}

char	**get_path(char **env)
{
	char	*tmp1;
	char	**tmp2;
	int		i;

	tmp1 = mini_getenv(env, "PATH");
	tmp2 = ft_split(tmp1, ':');
	i = -1;
	while (tmp2[++i])
		tmp2[i] = ft_strjoin_gnl(tmp2[i], "/");
	return (tmp2);
}

void	t_data_init(t_data *d, char **envp)
{
	d->env = dup_env(envp);
	d->path = get_path(d->env);
	d->pwd = ft_strdup(mini_getenv(d->env, "PWD"));
	d->oldpwd = ft_strdup(mini_getenv(d->env, "OLDPWD"));
	d->lex = NULL;
	d->pars = NULL;
	d->line = NULL;
	d->in = dup(STDIN_FILENO);
	d->out = dup(STDOUT_FILENO);
	d->exit = 0;
}
