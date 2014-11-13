/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/01 16:07:14 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/13 16:46:27 by mdiouf           ###   ########.fr       */
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
	printf("%s\n", *new_path);
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
			break;
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
			(*vars)->env[i] = ft_strjoin("OLDPWD=", ((*var)->old_path = ft_strdup((*var)->cur_path)));
			break;
		}
		i++;
	}
}

void		change_env_pwd(char **new_pwd, t_paths **var, t_main **vars)
{
	int		i;

	i = 0;
	change_old_pwd(vars, var);
	printf("new_pwd: %s\n", *new_pwd);
	change_pwd(new_pwd, vars, var);
	while ((*vars)->env[i] != NULL)
	{
		printf("%s\n", (*vars)->env[i]);
		i++;
	}
}

void		path_constr(t_paths **var, t_main **vars, char **split_path)
{
	int		i;
	char	*full_path;

	i = 0;
	full_path = ft_strdup((*var)->cur_path);
	var = var;
	while (split_path[i] != '\0')
	{
		if (i == 0 && (ft_strcmp(split_path[i], "~") == 0))
			full_path =  (*var)->cur_home;
		else if (ft_strcmp(split_path[i], "..") == 0)
			prev_folder(&full_path);
		else if (ft_strcmp(split_path[i], ".") != 0)
		{
			full_path = ft_strjoin(full_path, "/");
			full_path = ft_strjoin(full_path, split_path[i]);
		}
		i++;
	}
	if ((*var)->cur_path != NULL && full_path != NULL)
	{
		free((*var)->cur_path);
		(*var)->cur_path = full_path;
	}
	if (chdir((*var)->cur_path) == 0)
		change_env_pwd(&full_path, var, vars);
	else
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(full_path, 2);
		free(full_path);
		full_path = NULL;
		ft_putstr_fd("\n", 2);
	}
}

void		handle_cd(t_main **vars, t_paths **var)
{
	char	**split_path;

	split_path = NULL;
	split_path = ft_strsplit2((*vars)->split_args[1], '/');
	path_constr(var, vars, split_path);
}

void		cd_cmd(t_main **vars, t_paths **var)
{
	(*var)->cur_path = make_path(vars);
	(*var)->cur_home = get_home(vars);
	(*var)->old_path = get_old_pwd(vars);
	if (((*vars)->split_args[2] == NULL ) && (*vars)->split_args[1] != NULL)
		handle_cd(vars, var);
	else
	{
		ft_putstr("cd uses 1 argument only\n");
		exit(0);
	}
}
