/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 03:31:04 by mdiouf            #+#    #+#             */
/*   Updated: 2014/09/28 21:36:02 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	int		i;
	char	*newstring;
	int		length;

	length = ft_strlen(s);
	newstring = malloc((length + 1) * sizeof(char));
	i = 0;
	while (s[i] != '\0')
	{
		newstring[i] = f(i, s[i]);
		i++;
	}
	return (newstring);
}
