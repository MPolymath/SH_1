/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/06 18:47:02 by mdiouf            #+#    #+#             */
/*   Updated: 2014/10/12 18:14:51 by mdiouf           ###   ########.fr       */
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
	while (test_space_tab((*vars)->line, *size) == 0 && (*vars)->line[*size] != '\0')
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
		if (test_space_tab((*vars)->line, start) == 1 || (*vars)->line[start] == '\0')
		{
			args_nbr++;
			while (test_space_tab((*vars)->line, start) == 1)
				start++;
			if ((*vars)->line[start] == '\0')
				break;
		}
		else
			start++;
	}
	return (args_nbr);
}

void	get_size_str(t_main **vars, int i, int *size)
{
	while (test_space_tab((*vars)->line, i) == 0 && (*vars)->line[i] != '\0')
	{
		(*size)++;
		i++;
	}
}

void	fill_malloc_char(t_main **vars, int **start, int *i , int *j)
{
	while (test_space_tab((*vars)->line, **start) == 0 && (*vars)->line[**start] != '\0')
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
	(*vars)->split_args = (char**)malloc(sizeof(char*) * ((*vars)->args_nbr + 2));
	while ((*vars)->line[*start] != '\0')
	{
		var.tmp_start = *start;
		if ((test_space_tab((*vars)->line, *start) == 0))
		{
			get_size_str(vars, *start, &(var.size));
			(*vars)->split_args[var.i] = (char*)malloc(sizeof(char) * (var.size + 1));
			var.size = 0;
			*start = var.tmp_start;
			fill_malloc_char(vars, &start, &(var.i) , &(var.j));
			var.j = 0;
			(var.i)++;
		}
		while (test_space_tab((*vars)->line, *start) == 1)
			(*start)++;
	}
	(*vars)->split_args[var.i + 1] = '\0';
}

void	ft_split_args(t_main *vars)
{
	int	start;
	int	size;
	int	i;

	size = 0;
	start = 0;
	i = 0;
	vars->tmp = NULL;
	vars->split_args = NULL;
	ft_split_to_space(&vars, &start, &size);
//	if (vars->split_args != NULL)
		vars->command = ft_strdup(vars->tmp);
//	printf("vars->tmp: %s\n", vars->tmp);
//	if (vars->tmp != NULL)
//	{
//		free(vars->tmp);
//		vars->tmp = NULL;
//	}
	vars->args_nbr = count_args(&vars, start);
	start = 0;
	args_cpy(&vars, &start);
}
