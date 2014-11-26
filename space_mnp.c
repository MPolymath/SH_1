/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_mnp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/12 21:00:37 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/26 04:36:48 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int		test_space_tab(char *str, int i)
{
	if (str[i] == ' ' || str[i] == '\t')
		return (1);
	return (0);
}

void	ft_split_to_space(t_main **vars, int *start, int *size)
{
	*size = *start;
	while (test_space_tab((*vars)->line, *size) == 0 &&
							(*vars)->line[*size] != '\0')
		(*size)++;
	(*vars)->tmp = (char*)malloc(sizeof(char) * ((*size) - (*start) + 1));
	*size = *size + *start;
	while (*start != *size)
	{
		(*vars)->tmp[*start] = (*vars)->line[*start];
		(*start)++;
	}
	(*vars)->tmp[*start] = '\0';
	if (test_space_tab((*vars)->line, *start))
		while (test_space_tab((*vars)->line, *start))
			(*start)++;
}

int		count_args(t_main **vars, int start)
{
	int	args_nbr;

	args_nbr = 0;
	if ((*vars)->line[start] == '\0')
		return (0);
	while (1)
	{
		if (test_space_tab((*vars)->line, start) == 1 ||
							(*vars)->line[start] == '\0')
		{
			args_nbr++;
			while (test_space_tab((*vars)->line, start) == 1)
				start++;
			if ((*vars)->line[start] == '\0')
				break ;
		}
		else
			start++;
	}
	return (args_nbr);
}
