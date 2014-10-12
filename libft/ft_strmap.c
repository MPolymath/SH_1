/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 03:14:22 by mdiouf            #+#    #+#             */
/*   Updated: 2014/09/28 21:35:51 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char		*ft_strmap(char const *s, char (*f) (char))
{
	int		i;
	char	*newstring;

	newstring = malloc((ft_strlen(s) + 1) * sizeof(char));
	i = 0;
	while (s[i] != '\0')
	{
		newstring[i] = f(s[i]);
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}
