/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/29 02:31:34 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/26 05:00:19 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strtrim(char const *s)
{
	char	*newstring;

	newstring = malloc((ft_strlen(s) + 1) * sizeof(char*));
	if (newstring == NULL || !s)
		return (NULL);
	newstring = (char*)ft_begin_end_space_delete(s);
	return (newstring);
}
