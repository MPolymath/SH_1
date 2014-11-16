/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 20:21:31 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/16 20:41:41 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

char		*get_home(t_main **vars)
{
	t_make	var;

	get_home_init(&var);
	while ((*vars)->env[var.i] != '\0')
	{
		if ((*vars)->env[var.i][0] == 'H' && (*vars)->env[var.i][1] == 'O' &&
			(*vars)->env[var.i][2] == 'M' && (*vars)->env[var.i][3] == 'E' &&
			(*vars)->env[var.i][4] == '=')
		{
			var.length_path = ft_strlen((*vars)->env[var.i]) - 4;
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

char		*get_old_pwd(t_main **vars)
{
	t_make	var;

	get_old_init(&var);
	while ((*vars)->env[var.i] != '\0')
	{
		if ((*vars)->env[var.i][0] == 'O' && (*vars)->env[var.i][1] == 'L' &&
			(*vars)->env[var.i][2] == 'D' && (*vars)->env[var.i][3] == 'P' &&
			(*vars)->env[var.i][4] == 'W' && (*vars)->env[var.i][5] == 'D' &&
			(*vars)->env[var.i][6] == '=')
		{
			var.length_path = ft_strlen((*vars)->env[var.i]) - 6;
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

void		free_temp(char **temp)
{
	if (*temp != NULL)
	{
		free(*temp);
		*temp = NULL;
	}
}

void		change_pwd(char **new_path, t_main **vars, t_paths **var)
{
	int		i;

	i = 0;
	(*var)->cur_path = make_path(vars);
	(*var)->old_path = get_old_pwd(vars);
	while ((*vars)->env[i] != '\0')
	{
		if ((*vars)->env[i][0] == 'P' && (*vars)->env[i][1] == 'W' &&
			(*vars)->env[i][2] == 'D' && (*vars)->env[i][3] == '=')
		{
			free_temp(&(*vars)->env[i]);
			free_temp(&(*var)->cur_path);
			(*var)->cur_path = NULL;
			(*var)->cur_path = ft_strdup(*new_path);
			(*vars)->env[i] = ft_strjoin("PWD=", (*var)->cur_path);
			break ;
		}
		i++;
	}
}

void		change_old_pwd(t_main **vars, t_paths **var)
{
	int		i;

	i = 0;
	(*var)->cur_path = make_path(vars);
	(*var)->old_path = get_old_pwd(vars);
	while ((*vars)->env[i] != '\0')
	{
		if ((*vars)->env[i][0] == 'O' && (*vars)->env[i][1] == 'L' &&
			(*vars)->env[i][2] == 'D' && (*vars)->env[i][3] == 'P' &&
			(*vars)->env[i][4] == 'W' && (*vars)->env[i][5] == 'D' &&
			(*vars)->env[i][6] == '=')
		{
			free_temp(&(*vars)->env[i]);
			free_temp(&(*var)->old_path);
			(*var)->old_path = ft_strdup((*var)->cur_path);
			(*vars)->env[i] = ft_strjoin("OLDPWD=", (*var)->old_path);
			break ;
		}
		i++;
	}
}
