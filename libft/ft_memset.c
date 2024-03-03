/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:58:38 by albrusso          #+#    #+#             */
/*   Updated: 2022/11/11 15:47:55 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*d;
	size_t	i;

	i = 0;
	d = (char *)s;
	while (i < n)
	{
		d[i] = c;
		i++;
	}
	return (s);
}
