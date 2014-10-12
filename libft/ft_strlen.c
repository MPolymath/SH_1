/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 11:27:43 by mdiouf            #+#    #+#             */
/*   Updated: 2014/09/28 21:35:34 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_strlen(const char *string)
{
	int	length;

	length = 0;
	while (*string != '\0')
	{
		string++;
		length++;
	}
	return (length);
}
