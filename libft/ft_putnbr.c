/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 16:09:57 by mdiouf            #+#    #+#             */
/*   Updated: 2014/09/28 21:30:54 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putnbr(int i)
{
	static int	n = 0;

	if (i < 0)
	{
		i = -i;
		n = 1;
	}
	if (i > 9)
	{
		ft_putnbr(i / 10);
		ft_putnbr(i % 10);
	}
	else
	{
		if (n == 1)
		{
			ft_putchar('-');
			n = 0;
		}
		ft_putchar(48 + i);
	}
}
