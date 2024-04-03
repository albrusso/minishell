/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:16:10 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/03 15:20:43 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	executor(t_data *d)
{
	t_parser	*p;
	int			dup[2];

	p = d->pars;
	while (p)
	{
		if (p->n)
		{
			if (pipe(dup) < 0)
				exit(EXIT_FAILURE);
		}
		if (!p->n)
			execute_onecmd(d, p);
		else
			execute_fork(d, p);
		p = p->n;
	}
	
}