/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 20:21:28 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/16 20:43:26 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void		make_path_init(t_make *var)
{
	var->length_path = 0;
	var->i = 0;
	var->j = 4;
	var->k = 0;
}

void		get_home_init(t_make *var)
{
	var->length_path = 0;
	var->i = 0;
	var->j = 5;
	var->k = 0;
}

void		get_old_init(t_make *var)
{
	var->length_path = 0;
	var->i = 0;
	var->j = 7;
	var->k = 0;
}

void		prev_folder(char **cur_folder)
{
	int		i;
	int		temp;

	i = 0;
	temp = 0;
	while ((*cur_folder)[i] == '/')
		i++;
	if ((*cur_folder)[i] != '\0')
		temp = i;
	while ((*cur_folder)[i] != '\0')
	{
		while ((*cur_folder)[i] != '/' && (*cur_folder)[i] != '\0')
			i++;
		while ((*cur_folder)[i] == '/')
			i++;
		if ((*cur_folder)[i] != '\0')
			temp = i;
	}
	if ((*cur_folder)[temp - 1] == '/')
		(*cur_folder)[temp - 1] = '\0';
	while ((*cur_folder)[temp] != '\0')
	{
		(*cur_folder)[temp] = 0;
		temp++;
	}
}

char		*make_path(t_main **vars)
{
	t_make	var;

	make_path_init(&var);
	while ((*vars)->env[var.i] != '\0')
	{
		if ((*vars)->env[var.i][0] == 'P' && (*vars)->env[var.i][1] == 'W' &&
			(*vars)->env[var.i][2] == 'D' && (*vars)->env[var.i][3] == '=')
		{
			var.length_path = ft_strlen((*vars)->env[var.i]) - 3;
			var.path = (char*)malloc(sizeof(char) * var.length_path);
			while (((*vars)->env)[var.i][var.j] != '\0')
			{
				(var.path)[var.k] = ((*vars)->env)[var.i][var.j];
				(var.k)++;
				(var.j)++;
			}
			(var.path)[var.k] = '\0';
			break ;
		}
		(var.i)++;
	}
	return (var.path);
}
