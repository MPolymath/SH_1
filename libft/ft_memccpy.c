/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 21:00:54 by mdiouf            #+#    #+#             */
/*   Updated: 2014/09/28 21:27:48 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void				*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	unsigned char	*string1;
	unsigned char	*string2;
	size_t			i;

	i = 0;
	string1 = (unsigned char*)s1;
	string2 = (unsigned char*)s2;
	while (string2[i] != '\0' && i < n)
	{
		string1[i] = string2[i];
		i++;
		if (string2[i - 1] == c)
		{
			s1 = (void*)&string1[i];
			return (s1);
		}
	}
	return (NULL);
}
