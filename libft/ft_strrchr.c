/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 21:25:15 by mdiouf            #+#    #+#             */
/*   Updated: 2014/09/28 21:37:47 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;
	int	boolean;

	j = 0;
	i = 0;
	boolean = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			j = i;
			boolean = 1;
		}
		i++;
	}
	if (c == '\0')
		return ((char*)&s[i]);
	if (boolean == 1)
		return ((char*)&s[j]);
	return (NULL);
}
