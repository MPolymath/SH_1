/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/01 16:07:14 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/02 20:24:12 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

char		*make_path(t_main **vars)
{
	int		length_path;
	int		i;
	int		k;
	int		j;
	char	*path;

	length_path = 0;
	i = 0;
	j = 4;
	k = 0;
	while ((*vars)->env[i] != '\0')
	{
		if ((*vars)->env[i][0] == 'P' && (*vars)->env[i][1] == 'W' &&
			(*vars)->env[i][2] == 'D' && (*vars)->env[i][3] == '=')
		{
			length_path = ft_strlen((*vars)->env[i]) - 3;
			path = (char*)malloc(sizeof(char) * length_path);
			while (((*vars)->env)[i][j] != '\0')
			{
				path[k] = ((*vars)->env)[i][j];
				k++;
				j++;
			}
			path[k] = '\0';
			break;
		}
		i++;
	}
	return (path);
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
	int		length_path;
	int		i;
	int		k;
	int		j;
	char	*path;

	length_path = 0;
	i = 0;
	j = 5;
	k = 0;
	while ((*vars)->env[i] != '\0')
	{
		if ((*vars)->env[i][0] == 'H' && (*vars)->env[i][1] == 'O' &&
			(*vars)->env[i][2] == 'M' && (*vars)->env[i][3] == 'E' &&
			(*vars)->env[i][4] == '=')
		{
			length_path = ft_strlen((*vars)->env[i]) - 4;
			path = (char*)malloc(sizeof(char) * length_path + 1);
			while (((*vars)->env)[i][j] != '\0')
			{
				path[k] = ((*vars)->env)[i][j];
				k++;
				j++;
			}
			end_str(&path, k);
			break;
		}
		i++;
	}
	return (path);
}

char		*get_old_pwd(t_main **vars)
{
	int		length_path;
	int		i;
	int		k;
	int		j;
	char	*path;

	length_path = 0;
	i = 0;
	j = 7;
	k = 0;
	while ((*vars)->env[i] != '\0')
	{
		if ((*vars)->env[i][0] == 'O' && (*vars)->env[i][1] == 'L' &&
			(*vars)->env[i][2] == 'D' && (*vars)->env[i][3] == 'P' &&
			(*vars)->env[i][4] == 'W' && (*vars)->env[i][5] == 'D' &&
			(*vars)->env[i][6] == '=')
		{
			length_path = ft_strlen((*vars)->env[i]) - 6;
			path = (char*)malloc(sizeof(char) * length_path + 1);
			while (((*vars)->env)[i][j] != '\0')
			{
				path[k] = ((*vars)->env)[i][j];
				k++;
				j++;
			}
			end_str(&path, k);
			break;
		}
		i++;
	}
	return (path);
}

void		free_temp(char **temp)
{
	if (*temp != NULL)
	{
		free(*temp);
		*temp = NULL;
	}

}

void		change_pwd(char **new_path, t_main **vars)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while ((*vars)->env[i] != '\0')
	{
		if ((*vars)->env[i][0] == 'P' && (*vars)->env[i][1] == 'W' &&
			(*vars)->env[i][2] == 'D' && (*vars)->env[i][3] == '=')
		{
			free_temp(&(*vars)->env[i]);
			(*vars)->env[i] = ft_strjoin("PWD=", (temp = ft_strdup(*new_path)));
			free_temp(&temp);
			break;
		}
		i++;
	}

}

void		change_old_pwd(t_main **vars, t_paths **var)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while ((*vars)->env[i] != '\0')
	{
		if ((*vars)->env[i][0] == 'O' && (*vars)->env[i][1] == 'L' &&
			(*vars)->env[i][2] == 'D' && (*vars)->env[i][3] == 'P' &&
			(*vars)->env[i][4] == 'W' && (*vars)->env[i][5] == 'D' &&
			(*vars)->env[i][6] == '=')
		{
			free_temp(&(*vars)->env[i]);
			(*vars)->env[i] = ft_strjoin("OLDPWD=", (temp = ft_strdup((*var)->cur_path)));
			free_temp(&temp);
			break;
		}
		i++;
	}

}

void		change_env_pwd(char **new_pwd, t_paths **var, t_main **vars)
{
	int		i;

	i = 0;
	while ((*vars)->env[i] != NULL)
	{
		printf("%s\n", (*vars)->env[i]);
		i++;
	}
	change_old_pwd(vars, var);
	change_pwd(new_pwd, vars);
	i = 0;
	while ((*vars)->env[i] != NULL)
	{
		printf("%s\n", (*vars)->env[i]);
		i++;
	}
}

void		handle_cd(t_main **vars, t_paths *var)
{
	char	**split_path;

	split_path = NULL;
	split_path = ft_strsplit2((*vars)->split_args[1], '/');
	if (split_path[0][0] == '~' && split_path[0][1] == '\0')
	{
		chdir(var->cur_home);
		change_env_pwd(&(var->cur_home), &var, vars);
//change pwd oldpwd
	}
	else
		ft_putstr("Not handled Yet\n");
//	if (split_path == NULL)
//		ft_putstr("NULL\n");
//	while (split_path[i] != NULL)
//	{
//		printf("split_path[%d]: %s\n", i,split_path[i]);
//		i++;
//	}
}

void		cd_cmd(t_main **vars)
{
	t_paths	var;

	var.cur_path = make_path(vars);
	var.cur_home = get_home(vars);
	var.old_path = get_old_pwd(vars);
	printf("%s\n", var.cur_path);
	printf("%s\n", var.cur_home);
	printf("%s\n", var.old_path);
	printf("command :%s\n", (*vars)->command);
//	while ((*vars)->split_args[i] != NULL)
//	{
//		printf("split_args[%d] :%s\n", i, (*vars)->split_args[i]);
//		i++;
//	}
//if ~
	if (((*vars)->split_args[2] == NULL ) && (*vars)->split_args[1] != NULL)
		handle_cd(vars, &var);
	else
	{
		ft_putstr("cd uses 1 argument only\n");
		exit(0);
	}
	exit(0);
//if ~/ else if ~ invalid else ~\0
//if ..
//if ../ else if .. invalid else ..\0
//if .
//if ./ else if . invalid else .\0
//if /
//if ends with // or ./ * infinity
}
