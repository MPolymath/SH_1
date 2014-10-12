/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 21:19:01 by mdiouf            #+#    #+#             */
/*   Updated: 2014/09/28 21:38:14 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char			*pts1;
	unsigned int	i;
	unsigned int	j;

	i = start;
	j = 0;
	pts1 = malloc((len + 1) * sizeof(char*));
	if (len == 0 || pts1 == NULL)
	{
		return (NULL);
	}
	while (i >= start && i <= (start + (len - 1)))
	{
		pts1[j] = s[i];
		i++;
		j++;
	}
	pts1[j] = '\0';
	return (pts1);
}
