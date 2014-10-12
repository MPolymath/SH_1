/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_index_lastalnum.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/14 09:24:16 by mdiouf            #+#    #+#             */
/*   Updated: 2014/09/28 21:25:33 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_index_lastalnum(char const *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = ft_index_firstalnum(s);
	while (s[i] != '\0')
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
		{
			j = i;
		}
		i++;
	}
	return (j);
}
