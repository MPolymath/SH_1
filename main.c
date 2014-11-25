/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/06 17:17:43 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/25 01:21:40 by mdiouf           ###   ########.fr       */
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
	vars->temp_env = NULL;
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

void		while_funcs(t_main **vars, t_paths **var)
{
	ft_split_args(vars);
	(*vars)->list = split_pipe_and((*vars)->line);
	create_tree(&((*vars)->list), &((*vars)->var));
	if (ft_strcmp((*vars)->command, "exit") == 0)
		exit(0);
	else if (ft_strcmp((*vars)->command, "cd") == 0)
		execute(vars, var);
	else if (ft_strcmp((*vars)->command, "setenv") == 0)
		execute(vars, var);
	else if (ft_strcmp((*vars)->command, "unsetenv") == 0)
		execute(vars, var);
	else if (ft_strcmp((*vars)->command, "env") == 0)
		execute(vars, var);
	else
		ft_fork(vars, var);
}

void		main_body(t_main *vars)
{
	if (vars->split_args != NULL)
	{
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
	t_main	*temp2;
	t_paths var;
	t_paths *temp;

	temp = &var;
	temp2 = &vars;
	if (envp[0] == NULL)
	{
		ft_putstr_fd("Program cannot run without env\n", 2);
		return (0);
	}
	init_main(&vars, argc, argv);
	cpy_env(envp, &vars);
	vars.paths = ft_split_path(envp, &(vars.env));
	while (get_next_line(vars.fd, &(vars.line)))
	{
		if (vars.line != NULL)
		{
			while_funcs(&temp2, &temp);
			main_body(&vars);
		}
		ft_putstr("$> ");
	}
	return (0);
}
