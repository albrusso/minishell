/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:01:23 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/08 17:24:08 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit = 0;

void	run_shell(t_data *d, t_message *m);

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

void	clean_exit(t_data *d, t_message *m, bool _exit)
{
	if (d)
		t_data_free(d, _exit);
	if (m)
		t_message_free(m);
	if (_exit)
		exit(g_exit);
	else
	{
		d->restart = true;
		run_shell(d, m);
	}
}

void	run_shell(t_data *d, t_message *m)
{
	char	*tmp;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	t_message_init(m, d->env);
	tmp = readline(m->msg);
	if (tmp)
		d->line = ft_strtrim(tmp, " ");
	free(tmp);
	if (!d->line || !ft_strncmp(d->line, "exit", 4))
		clean_exit(d, m, true);
	if (d->line[0] == '\0')
		clean_exit(d, m, false);
	add_history(d->line);
	lexer(d);
	parser(d);
	//executer(d, d->pars);
	clean_exit(d, m, false);
}

int	main(int ac, char **av, char **envp)
{
	t_data		d;
	t_message	m;

	if (ac != 1 || av[1])
		return (0);
	t_data_init(&d, envp);
	run_shell(&d, &m);
	return (0);
}
