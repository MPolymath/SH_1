/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 19:07:18 by mdiouf            #+#    #+#             */
/*   Updated: 2014/09/28 21:24:11 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_atoi(const char *str)
{
	int	length;
	int	i;
	int	negative;
	int	sum;

	negative = 1;
	i = 0;
	sum = 0;
	length = ft_strlen(str);
	if (str[i] == '-')
	{
		negative = -1;
		i++;
		length--;
	}
	if (str[i] == '+')
		i++;
	sum = ft_atoi2(i, length, negative, str);
	return (sum);
}
