/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:52:05 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/04 18:01:42 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_shell
{
		t_list	*env;
		char	**path;
		char	*prompt;
}		t_shell;

t_list	*get_env(char **envp);
char	**get_path(void);

void free_lst(t_list **lst);
void	free_array(char **arr);




#endif