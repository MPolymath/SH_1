/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 18:32:13 by mdiouf            #+#    #+#             */
/*   Updated: 2014/09/28 21:27:18 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	convert_nb_string(char **stringptd, int *i, int *nbr)
{
	int		tmp;
	int		chiffre;
	int		size;

	tmp = *nbr;
	size = 1;
	while (tmp / 9 > 0)
	{
		size = size * 10;
		tmp = tmp / 10;
	}
	while (size > 0)
	{
		chiffre = 0;
		chiffre = (*nbr) / size;
		(*stringptd)[*i] = '0' + chiffre;
		(*i)++;
		*nbr = *nbr % size;
		size = size / 10;
	}
	return (0);
}

char	*ft_itoa(int nbr)
{
	int		i;
	char	*stringptd;

	stringptd = malloc(3 * sizeof(char));
	i = 0;
	if (nbr < 0)
	{
		stringptd[i] = '-';
		nbr = nbr * -1;
		i++;
	}
	convert_nb_string(&stringptd, &i, &nbr);
	return (stringptd);
}
