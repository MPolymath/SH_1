/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/06 18:47:02 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/01 15:02:13 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void	get_size_str(t_main **vars, int i, int *size)
{
	while (test_space_tab((*vars)->line, i) == 0 && (*vars)->line[i] != '\0')
	{
		(*size)++;
		i++;
	}
}

void	fill_malloc_char(t_main **vars, int **start, int *i, int *j)
{
	while (test_space_tab((*vars)->line, **start) == 0
							&& (*vars)->line[**start] != '\0')
	{
		(*vars)->split_args[*i][*j] = (*vars)->line[**start];
		(**start)++;
		(*j)++;
	}
	(*vars)->split_args[*i][*j] = '\0';
}

void	init_var(t_args *var)
{
	var->size = 0;
	var->i = 0;
	var->j = 0;
	var->tmp_start = 0;
}

void	args_cpy(t_main **vars, int *start)
{
	t_args var;

	init_var(&var);
	(*vars)->split_args = (char**)malloc(sizeof(char*) *
									((*vars)->args_nbr + 2));
	while ((*vars)->line[*start] != '\0')
	{
		var.tmp_start = *start;
		if ((test_space_tab((*vars)->line, *start) == 0))
		{
			get_size_str(vars, *start, &(var.size));
			(*vars)->split_args[var.i] = (char*)malloc(sizeof(char) *
														(var.size + 1));
			var.size = 0;
			*start = var.tmp_start;
			fill_malloc_char(vars, &start, &(var.i), &(var.j));
			var.j = 0;
			(var.i)++;
		}
		while (test_space_tab((*vars)->line, *start) == 1)
			(*start)++;
	}
	(*vars)->split_args[var.i] = '\0'; //i+1 might be
}

void	ft_split_args(t_main **vars)
{
	int	start;
	int	size;

	size = 0;
	start = 0;
	(*vars)->tmp = NULL;
	(*vars)->split_args = NULL;
	ft_split_to_space(vars, &start, &size);
	(*vars)->command = ft_strdup((*vars)->tmp);
	(*vars)->args_nbr = count_args(vars, start);
	start = 0;
	args_cpy(vars, &start);
}
