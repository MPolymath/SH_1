/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 17:16:37 by mdiouf            #+#    #+#             */
/*   Updated: 2014/09/28 21:29:15 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void				*ft_memmove(void *s1, const void *s2, size_t n)
{
	unsigned char	*string1;
	unsigned char	*string2;
	unsigned char	*buffer;
	size_t			i;

	i = 0;
	string1 = (unsigned char*)s1;
	string2 = (unsigned char*)s2;
	buffer = malloc((n + 1) * sizeof(char));
	buffer = string2;
	while (string2[i] != '\0' && i < n)
	{
		string1[i] = buffer[i];
		i++;
	}
	if (i != n)
		string1[i] = buffer[i];
	s1 = (void*)string1;
	return (s1);
}
