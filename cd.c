/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/01 16:07:14 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/03 17:39:21 by mdiouf           ###   ########.fr       */
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
			break;
		}
		(var.i)++;
	}
	return (var.path);
}

void		end_str(char **path, int k)
{
	if ((*path)[k - 1] == '/')
	{
		(*path)[k] = '\0';
		(*path)[k + 1] = '\0';
	}
	else
	{
		(*path)[k] = '/';
		(*path)[k + 1] = '\0';
	}
}

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
			break;
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
			(*vars)->env[var.i][6] == '=' )
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
			break;
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
			(*vars)->env[i] = ft_strjoin("PWD=", ((*var)->cur_path = ft_strdup(*new_path)));
//			printf("new->cur_path: %s\n", (*var)->old_path);
//			printf("new->old_path: %s\n", (*var)->old_path);
//			printf("(*vars)->env[%d]: %s\n", i, (*vars)->env[i]);
			break;
		}
		i++;
	}
	printf("new->cur_path: %s\n", (*var)->cur_path);
	printf("new->old_path: %s\n", (*var)->old_path);
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
			(*vars)->env[i] = ft_strjoin("OLDPWD=", ((*var)->old_path = ft_strdup((*var)->cur_path)));
//			printf("old->cur_path: %s\n", (*var)->cur_path);
//			printf("old->old_path: %s\n", (*var)->old_path);
//			printf("(*vars)->env[%d]: %s\n", i, (*vars)->env[i]);
			break;
		}
		i++;
	}
	printf("old->cur_path: %s\n", (*var)->cur_path);
	printf("old->old_path: %s\n", (*var)->old_path);
}

void		change_env_pwd(char **new_pwd, t_paths **var, t_main **vars)
{
//	int		i;

//	i = 0;
//	while ((*vars)->env[i] != NULL)
//	{
//		printf("%s\n", (*vars)->env[i]);
//		i++;
//	}
	change_old_pwd(vars, var);
	change_pwd(new_pwd, vars, var);
//	i = 0;
//	while ((*vars)->env[i] != NULL)
//	{
//		printf("%s\n", (*vars)->env[i]);
//		i++;
//	}
}

void		handle_cd(t_main **vars, t_paths **var)
{
	char	**split_path;

	split_path = NULL;
	split_path = ft_strsplit2((*vars)->split_args[1], '/');
	if (split_path[0][0] == '~' && split_path[0][1] == '\0')
	{
		change_env_pwd(&((*var)->cur_home), var, vars); // add if ~ twice and already at home dont change anything;
		chdir((*var)->cur_home);
//change pwd oldpwd
	}
	else if (split_path[0][0] == '.' && split_path[0][1] == '.' && split_path[0][2] == '\0')
	{
		prev_folder(&((*var)->cur_home));
		change_env_pwd(&((*var)->cur_home), var, vars);
		chdir((*var)->cur_home);
	}
	else if (split_path[0][0] == '.' && split_path[0][1] == '\0')
	{
		change_env_pwd(&((*var)->cur_home), var, vars);
		chdir((*var)->cur_home);
//change pwd oldpwd
	}
	else if  (split_path[0][0] == '.' && split_path[0][0] == '~')
	{
//build new path
//change env;
	}
	else
		ft_putstr("Not handled Yet\n");
}

void		cd_cmd(t_main **vars, t_paths **var)
{
	(*var)->cur_path = make_path(vars);
	(*var)->cur_home = get_home(vars);
	(*var)->old_path = get_old_pwd(vars);
//	printf("(*vars)->env[13]: %s\n", (*vars)->env[13]);
//	printf("(*vars)->env[19]: %s\n", (*vars)->env[19]);
//	printf("%s\n", (*var)->cur_path);
//	printf("%s\n", (*var)->cur_home);
//	printf("%s\n", (*var)->old_path);
//	printf("command :%s\n", (*vars)->command);
//	while ((*vars)->split_args[i] != NULL)
//	{
//		printf("split_args[%d] :%s\n", i, (*vars)->split_args[i]);
//		i++;
//	}
//if ~
	if (((*vars)->split_args[2] == NULL ) && (*vars)->split_args[1] != NULL)
		handle_cd(vars, var);
	else
	{
		ft_putstr("cd uses 1 argument only\n");
		exit(0);
	}
//	printf("last->cur_path: %s\n", (*var)->cur_path);
//	printf("last->old_path: %s\n", (*var)->old_path);
//	printf("(*vars)->env[13]: %s\n", (*vars)->env[13]);
//	printf("(*vars)->env[19]: %s\n", (*vars)->env[19]);
//	exit(0);
//if ~/ else if ~ invalid else ~\0
//if ..
//if ../ else if .. invalid else ..\0
//if .
//if ./ else if . invalid else .\0
//if /
//if ends with // or ./ * infinity
}
