/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:51:40 by albrusso          #+#    #+#             */
/*   Updated: 2024/02/08 16:26:27 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_null_path(t_shell *root)
{
	int	ret;
	char	*buff;

	ret = chdir(root->home_pwd);
	if (ret == -1)
		ft_clean_exit(root);
	free(root->old_pwd);
	root->old_pwd = ft_strdup(root->curr_pwd);
	buff = malloc(sizeof(char) * 1024);
	getcwd(buff, 1024);
	free(root->curr_pwd);
	root->curr_pwd = ft_strdup(buff);
	free(buff);
}

int	ft_cd(const char *path, t_shell *root)
{
	int		ret;
	char	*buff;
	
	if (!path)
		ft_null_path(root);
	else
	{
		ret = chdir(path);
		if (ret == -1)
			ft_clean_exit(root);
		free(root->old_pwd);
		root->old_pwd = ft_strdup(root->curr_pwd);
		buff = malloc(sizeof(char) * 1024);
		getcwd(buff, 1024);
		free(root->curr_pwd);
		root->curr_pwd = ft_strdup(buff);
		free(buff);
	}
	return (1);
}