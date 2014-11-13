/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/11 21:08:25 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/13 16:50:32 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdio.h>

void	count_words2(char const *s, char c, t_split *vars)
{
	while (1)
	{
		if (s[vars->i] != c && s[vars->i] != '\0')
		{
			(vars->nbr_words)++;
			while (s[vars->i] != c && s[vars->i] != '\0')
				(vars->i)++;
		}
		else if (s[vars->i] == '\0')
		{
			break ;
		}
		else
			(vars->i)++;
	}
	(vars->i) = 0;
}

void	fill_split_skip_c2(char const *s, char c, t_split **vars)
{
	if ((*vars)->k != 0)
		(*vars)->split_c[(*vars)->j][(*vars)->k] = '\0';
	(*vars)->k = 0;
	(*vars)->nbr_chars = 0;
	while (s[(*vars)->i] == c)
		((*vars)->i)++;
}

void	fill_dbl_ptr2(char const *s, char c, t_split **vars)
{
	(*vars)->start = (*vars)->i;
	if ((*vars)->nbr_chars == 0)
	{
		while (s[(*vars)->start] != c && s[(*vars)->start] != '\0')
		{
			((*vars)->nbr_chars)++;
			((*vars)->start)++;
		}
		(*vars)->split_c[(*vars)->j] = (char*)malloc(sizeof(char) *
									((*vars)->nbr_chars + 1));
	}
	(*vars)->split_c[(*vars)->j][(*vars)->k] = s[(*vars)->i];
	((*vars)->k)++;
	((*vars)->i)++;
}

void	fill_split_c2(char const *s, char c, t_split *vars)
{
	while (1)
	{
		if (s[vars->i] == c && vars->nbr_chars != 0)
		{
			fill_split_skip_c2(s, c, &vars);
			(vars->j)++;
		}
		else if (s[vars->i] == c && vars->nbr_chars == 0)
			fill_split_skip_c2(s, c, &vars);
		else if (s[vars->i] != c && s[vars->i] != '\0')
			fill_dbl_ptr2(s, c, &vars);
		else if (s[vars->i] == '\0')
		{
			if (vars->k != 0)
			{
				vars->split_c[vars->j][vars->k] = '\0';
				(vars->j)++;
			}
			break ;
		}
	}
	vars->split_c[vars->j] = NULL;
}

char	**ft_strsplit2(char const *s, char c)
{
	t_split vars;

	vars.i = 0;
	vars.j = 0;
	vars.k = 0;
	vars.nbr_words = 0;
	vars.nbr_chars = 0;
	vars.start = 0;
	count_words2(s, c, &vars);
	vars.split_c = (char**)malloc(sizeof(char*) * (vars.nbr_words + 1));
	fill_split_c2(s, c, &vars);
	return (vars.split_c);
}
