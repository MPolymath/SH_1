/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/01 16:07:14 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/16 20:31:09 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void		change_env_pwd(char **new_pwd, t_paths **var, t_main **vars)
{
	change_old_pwd(vars, var);
	change_pwd(new_pwd, vars, var);
}

void		build_path(t_paths **var, int *i, char **full_path,
						char **split_path)
{
	while (split_path[*i] != '\0')
	{
		if (*i == 0 && (ft_strcmp(split_path[*i], "~") == 0))
			*full_path = (*var)->cur_home;
		else if (ft_strcmp(split_path[*i], "..") == 0)
			prev_folder(full_path);
		else if (ft_strcmp(split_path[*i], ".") != 0)
		{
			*full_path = ft_strjoin(*full_path, "/");
			*full_path = ft_strjoin(*full_path, split_path[*i]);
		}
		(*i)++;
	}
}

void		path_unfound(char **full_path)
{
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putstr_fd(*full_path, 2);
	free(*full_path);
	*full_path = NULL;
	ft_putstr_fd("\n", 2);
}

void		path_constr(t_paths **var, t_main **vars, char **split_path)
{
	int		i;
	char	*full_path;

	i = 0;
	full_path = ft_strdup((*var)->cur_path);
	var = var;
	if ((*vars)->split_args[1] == '\0')
		full_path = (*var)->cur_home;
	else if (ft_strcmp((*vars)->split_args[1], "-") == 0 &&
			(*vars)->split_args[2] == NULL)
		full_path = (*var)->old_path;
	else
		build_path(var, &i, &full_path, split_path);
	if ((*var)->cur_path != NULL && full_path != NULL)
	{
		free((*var)->cur_path);
		(*var)->cur_path = full_path;
	}
	if (chdir((*var)->cur_path) == 0)
		change_env_pwd(&full_path, var, vars);
	else
		path_unfound(&full_path);
}

void		handle_cd(t_main **vars, t_paths **var)
{
	char	**split_path;

	split_path = NULL;
	if ((*vars)->split_args[1] != NULL)
		split_path = ft_strsplit2((*vars)->split_args[1], '/');
	path_constr(var, vars, split_path);
}
