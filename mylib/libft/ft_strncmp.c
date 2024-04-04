/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:02:54 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/04 15:29:04 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	if ((!str1 || !str2) && str1 != str2)
		return (1);
	else if ((!str1 || !str2) && str1 == str2)
		return (0);
	i = 0;
	while (i < n)
	{
		if (str1[i] == str2[i] && (str1[i] && str2[i]))
			i++;
		else
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	}
	return (0);
}
