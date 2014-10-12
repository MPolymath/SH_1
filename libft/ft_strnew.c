/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 23:05:30 by mdiouf            #+#    #+#             */
/*   Updated: 2014/09/28 21:37:03 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnew(size_t size)
{
	char	*ptnewstring;
	size_t	i;

	ptnewstring = malloc(size * (sizeof(char)));
	i = 0;
	if (ptnewstring == NULL || size == 0)
	{
		return (NULL);
	}
	while (i < size)
	{
		ptnewstring[i] = '\0';
		i++;
	}
	return (ptnewstring);
}
