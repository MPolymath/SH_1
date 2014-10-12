/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 19:15:39 by mdiouf            #+#    #+#             */
/*   Updated: 2014/09/28 21:37:15 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	if (*s2 == '\0')
		return ((char*)s1);
	if (n < (size_t)ft_strlen(s2) || ft_strlen(s1) < ft_strlen(s2))
		return (NULL);
	while (*s1 != '\0' && n >= ((size_t)ft_strlen(s2)))
	{
		if (*s1 != s2[0])
			s1++;
		if (*s1 == s2[0])
		{
			if (ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
				return ((char*)s1);
			if (ft_strncmp(s1, s2, ft_strlen(s2)) != 0)
				s1++;
		}
		n--;
	}
	return (NULL);
}
