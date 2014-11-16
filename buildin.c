/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/12 20:50:44 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/16 17:39:31 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void		unsetenv_cmd(t_main **vars)
{
	vars = vars;
	unset_var(vars);
	ft_putstr(" unsetenv is not done\n");
}

void		setenv_cmd(t_main **vars)
{
	vars = vars;
	if (((*vars)->split_args)[0] != NULL &&
		((*vars)->split_args)[1] != NULL && ((*vars)->split_args)[2] != NULL
		&& ((*vars)->split_args)[3] == NULL)
		set_var(vars);
}

void		env_cmd(t_main **vars, t_paths **var)
{
	vars = vars;
	ft_env(vars, var);
	if ((*vars)->temp_env != NULL)
	{
		if ((*vars)->env != NULL)
		{
			free((*vars)->env);
			(*vars)->env = NULL;
		}
		(*vars)->env = (*vars)->temp_env;
		(*vars)->temp_env = NULL;
	}
}

void		cd_cmd(t_main **vars, t_paths **var)
{
	(*var)->cur_path = make_path(vars);
	(*var)->cur_home = get_home(vars);
	(*var)->old_path = get_old_pwd(vars);
	if (((*vars)->split_args[1] == NULL || (*vars)->split_args[2] == NULL))
		handle_cd(vars, var);
	else
	{
		ft_putstr("cd uses 1 argument only\n");
		exit(0);
	}
}
