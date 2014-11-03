/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/06 17:17:43 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/03 16:29:27 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"
#include "get_next_line.h"

void		init_main(t_main *vars, int argc, char **argv)
{
	vars->fd = 0;
	vars->args_nbr = 0;
	vars->i = 0;
	vars->env = NULL;
	vars->line = NULL;
	vars->tmp = NULL;
	vars->command = NULL;
	vars->test_path = NULL;
	vars->paths = NULL;
	vars->split_args = NULL;
	argc = argc;
	argv = argv;
	ft_putstr("$> ");
}

void		while_funcs(t_main *vars)
{
	t_paths var;
	t_paths *temp;

//	(var).cur_path = make_path(&vars);
//	(var).cur_home = get_home(&vars);
//	(var).old_path = get_old_pwd(&vars);
	temp = &var;
	ft_split_args(&vars);
	if (ft_strcmp(vars->command, "cd") == 0)
		execute(vars, &temp);
	else if (ft_strcmp(vars->command, "setenv") == 0)
		execute(vars, &temp);
	else if (ft_strcmp(vars->command, "unsetenv") == 0)
		execute(vars, &temp);
	else if (ft_strcmp(vars->command, "env") == 0)
		execute(vars, &temp);
	else
		ft_fork(&vars, &var);
	ft_putstr("$> ");
}

void		main_body(t_main *vars)
{
	if (vars->split_args != NULL)
	{
/*		while (vars->split_args[vars->i] != NULL)
		{
			free(vars->split_args[vars->i]);
			vars->split_args[vars->i] = NULL;
			(vars->i)++;
		}*/
		free(vars->split_args);
		vars->split_args = NULL;
	}
	if (vars->command != NULL)
	{
		free(vars->command);
		vars->command = NULL;
	}
}

int			main(int argc, char **argv, char **envp)
{
	t_main	vars;

	init_main(&vars, argc, argv);
	cpy_env(envp, &vars);
	vars.paths = ft_split_path(envp, &(vars.env));
	while (get_next_line(vars.fd, &(vars.line)))
	{
		if (vars.line != NULL)
		{
			while_funcs(&vars);
			main_body(&vars);
		}
		else
			ft_putstr("$> ");
	}
	return (0);
}
