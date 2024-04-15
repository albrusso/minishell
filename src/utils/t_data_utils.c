/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:04:43 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/15 17:11:40 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	t_data_free(t_data *d, bool _exit)
{
	if (_exit)
	{
		if (d->env)
			free_arr(d->env);
		if (d->path)
			free_arr(d->path);
		if (d->pwd)
			free(d->pwd);
		if (d->oldpwd)
			free(d->oldpwd);
		rl_clear_history();
	}
	if (d->line)
		free(d->line);
	d->line = NULL;
	if (d->lex)
		t_lexer_free(&d->lex);
	if (d->pars)
		t_parser_free(&d->pars);
}

void	t_data_init(t_data *d, char **envp)
{
	d->env = dup_arr(envp);
	d->path = get_path(d->env);
	d->pwd = ft_strdup(mini_getenv(d->env, "PWD"));
	d->oldpwd = ft_strdup(mini_getenv(d->env, "OLDPWD"));
	d->lex = NULL;
	d->pars = NULL;
	d->line = NULL;
	d->in = dup(STDIN_FILENO);
	d->out = dup(STDOUT_FILENO);
	d->exit = 0;
	d->restart = false;
}
