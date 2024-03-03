/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:36:40 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/03 17:17:36 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_data
{
	t_list	*env;
	char	**path;
	char	*prompt;
}		t_data;

void	init_data(t_data *d, char **envp);

int	arrlen(char **arr);

t_list	*get_env(char **envp);
char	**get_path(void);





#endif