/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:01:23 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/16 15:34:57 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit = 0;

int	run_shell(t_data *d);

void	free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		if (arr[i])
			free(arr[i]);
	}
	free(arr);
	arr = NULL;
}

int	clean_exit(t_data *d, t_message *m, bool _exit)
{
	unlink("heredoc");
	if (d)
		t_data_free(d, _exit);
	if (m)
		t_message_free(m);
	if (_exit)
		exit(g_exit);
	else
	{
		d->restart = true;
		if (!d->path)
			d->path = get_path(d->env);
		run_shell(d);
	}
	return (1);
}

int	run_shell(t_data *d)
{
	char	*tmp;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	t_message_init(&d->m, d->env);
	tmp = readline(d->m.msg);
	if (tmp)
		d->line = ft_strtrim(tmp, " ");
	free(tmp);
	if (!d->line)
		return (printf("exit\n"), clean_exit(d, &d->m, true));
	if (d->line[0] == '\0')
		return (clean_exit(d, &d->m, false));
	add_history(d->line);
	if (!match_quote(d->line))
		return (mini_error(d, 1, false));
	if (!lexer(d))
		return (clean_exit(d, &d->m, false));
	parser(d);
	executer(d, d->pars);
	clean_exit(d, &d->m, false);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_data		d;

	if (ac != 1 || av[1])
		return (0);
	t_data_init(&d, envp);
	run_shell(&d);
	return (0);
}
