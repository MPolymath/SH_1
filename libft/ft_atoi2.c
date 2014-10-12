/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/14 08:58:42 by mdiouf            #+#    #+#             */
/*   Updated: 2014/09/28 21:24:25 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_atoi2(int i, int length, int negative, char const *str)
{
	int	sum;
	int	count;

	sum = 0;
	count = 0;
	while (count != length)
	{
		if (ft_isdigit(str[i]) == 1)
		{
			sum = ((str[i] - '0') * ft_multiplier(1, length)) + sum;
			i++;
			length--;
		}
		else
		{
			sum = (sum * negative) / ft_multiplier(1, length + 1);
			return (sum);
		}
	}
	sum = sum * negative;
	return (sum);
}
