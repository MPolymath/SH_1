/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 17:43:53 by mdiouf            #+#    #+#             */
/*   Updated: 2014/09/28 21:35:22 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	int		maxsize;
	size_t	totallength;

	maxsize = size - ft_strlen(dst) - 1;
	totallength = 0;
	if (maxsize > 0)
	{
		totallength = ft_strlen(dst) + ft_strlen(src);
		dst = ft_strncat(dst, src, maxsize);
	}
	if (maxsize <= 0)
	{
		totallength = ft_strlen(src) + size;
	}
	return (totallength);
}
