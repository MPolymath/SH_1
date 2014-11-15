/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/27 21:40:37 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/15 19:57:13 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdio.h>

char	*ft_strdup(const char *s1)
{
	char	*dest;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	printf("length: %zu\n", len);
	dest = (char *)malloc((len + 1) * sizeof(char));
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
