/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 16:49:02 by mdiouf            #+#    #+#             */
/*   Updated: 2014/09/28 21:28:13 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int			ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*string1;
	char	*string2;
	size_t	i;
	int		total;

	string1 = (char*)s1;
	string2 = (char*)s2;
	i = 0;
	while (i < n)
	{
		if (string1[i] != string2[i])
		{
			total = (int)(string1[i] - string2[i]);
			return (total);
		}
		i++;
	}
	return (0);
}
