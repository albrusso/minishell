/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:51:40 by albrusso          #+#    #+#             */
/*   Updated: 2024/02/08 16:18:02 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(const char *path, t_shell *root)
{
	int		ret;
	char	*tmp;
	char	*buff;
	
	if (!path)
	{
		ret = chdir(root->home_pwd);
		if (ret == -1)
			exit(0);
		free(root->old_pwd);
		tmp = ft_strdup(root->curr_pwd);
		root->old_pwd = ft_strdup(tmp);
		buff = malloc(sizeof(char) * 1024);
		getcwd(buff, 1024);
		free(root->curr_pwd);
		root->curr_pwd = ft_strdup(buff);
		free(buff);
		free(tmp);
		return(1);
	}
	ret = chdir(path);
	if (ret == -1)
		exit(0);
	free(root->old_pwd);
	tmp = ft_strdup(root->curr_pwd);
	root->old_pwd = ft_strdup(tmp);
	buff = malloc(sizeof(char) * 1024);
	getcwd(buff, 1024);
	free(root->curr_pwd);
	root->curr_pwd = ft_strdup(buff);
	free(buff);
	free(tmp);
	return (1);
}