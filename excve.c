/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/12 13:38:02 by mdiouf            #+#    #+#             */
/*   Updated: 2014/10/12 20:44:48 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void		cd_cmd(t_main **vars)
{
	ft_putstr(" cd is not done\n");
}

void		setenv_cmd(t_main **vars)
{
	char	*new_env;

/*	if ((*vars)->split_args[1] != NULL &&
		(*vars)->split_args[2] != NULL && (*vars)->split_args[3] == NULL)
	{
		new_env = ft_strjoin((*vars)->split_args[1], "=");
		new_env = ft_strjoin(new_env, (*vars)->split_args[2]);
	}
	else
	{
		ft_putstr(" setenv wrong number of arguments\n");
		exit(0);
	}*/
	ft_putstr(" setenv is not done\n");
}

void		unsetenv_cmd(t_main **vars)
{
	ft_putstr(" unsetenv is not done\n");
}

void		env_cmd(t_main **vars)
{
	ft_putstr(" env is not done\n");
}

void		exec_others_cmd(t_main **vars)
{
	int		i;

	i = 0;
	(*vars)->test_path = NULL;
	if ((*vars)->paths != NULL)
	{
		while ((*vars)->paths[i] != '\0')
		{
//			if ((*vars)->test_path != NULL)
//			{
//				free((*vars)->test_path);
//				(*vars)->test_path = NULL;
//			}
			(*vars)->test_path = ft_strjoin((*vars)->paths[i], (*vars)->command);
			execve((*vars)->test_path, (*vars)->split_args, (*vars)->env);
			i++;
		}
		ft_putstr((*vars)->command);
		ft_putstr(": command not found\n");
	}
}

void		execute(t_main *vars)
{
	if (ft_strcmp(vars->command, "cd") == 0)
		cd_cmd(&vars);
	else if (ft_strcmp(vars->command, "setenv") == 0)
		setenv_cmd(&vars);
	else if (ft_strcmp(vars->command, "unsetenv") == 0)
		unsetenv_cmd(&vars);
	else if (ft_strcmp(vars->command, "env") == 0)
		env_cmd(&vars);
	else
		exec_others_cmd(&vars);
}
