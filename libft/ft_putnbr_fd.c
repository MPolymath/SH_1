/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 16:09:57 by mdiouf            #+#    #+#             */
/*   Updated: 2014/09/28 21:31:07 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putnbr_fd(int i, int fd)
{
	static int	n = 0;

	if (i < 0)
	{
		i = -i;
		n = 1;
	}
	if (i > 9)
	{
		ft_putnbr_fd(i / 10, fd);
		ft_putnbr_fd(i % 10, fd);
	}
	else
	{
		if (n == 1)
		{
			ft_putchar_fd('-', fd);
			n = 0;
		}
		ft_putchar_fd(48 + i, fd);
	}
}
