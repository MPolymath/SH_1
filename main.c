/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/06 17:17:43 by mdiouf            #+#    #+#             */
/*   Updated: 2014/12/04 19:54:56 by mdiouf           ###   ########.fr       */
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
	vars->line2 = NULL;
	vars->tmp = NULL;
	vars->tmp2 = NULL;
	vars->cmd_list = NULL;
	vars->cmd_list2 = NULL;
	vars->command = NULL;
	vars->test_path = NULL;
	vars->paths = NULL;
	vars->split_args = NULL;
	vars->split_args2 = NULL;
	argc = argc;
	argv = argv;
	ft_putstr("$> ");
}

void		while_funcs(t_main **vars, t_paths **var)
{
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

void		while_tree(t_main **vars, t_paths **var)
{
	t_tree	*temp;
	int		i;

	i = 0;
	(*vars)->pipe_fd[0] = -1;
	(*vars)->pipe_fd[1] = -1;
	temp = (*vars)->var.root; // initialise to first command
	(*vars)->type = 0;
	if (ft_strcmp(temp->left->cmd, ";") == 0) // ; handling
	{
		(*vars)->type = 1;
		if (temp->left->left_two != NULL)
		{
			temp = temp->left->left_two;
			if((*vars)->line != NULL)
			{
				free((*vars)->line);
				(*vars)->line = NULL;
				(*vars)->line = temp->cmd;
			}
			if((*vars)->split_args != NULL)
			{
				free((*vars)->split_args);
				(*vars)->split_args = NULL;
			}
			ft_split_args(vars);
			(*vars)->cmd_list = str_split_pipes(temp->cmd);
			while_funcs(vars, var);
			temp = (*vars)->var.root;
			if (temp->left->right_two != NULL)
			{
				temp = (*vars)->var.root->left->right_two;
				if((*vars)->line != NULL)
				{
					free((*vars)->line);
					(*vars)->line = NULL;
					(*vars)->line = temp->cmd;
				}
				if((*vars)->split_args != NULL)
				{
					free((*vars)->split_args);
					(*vars)->split_args = NULL;
				}
				ft_split_args(vars);
				(*vars)->cmd_list = str_split_pipes(temp->cmd);
				while_funcs(vars, var);
			}
		}
	}
	else if (ft_strcmp(temp->left->cmd, "|") == 0)
	{
		(*vars)->type = 2;
		if (temp->left->left_two != NULL)
		{
			temp = temp->left->left_two;
			if((*vars)->line != NULL)
			{
				free((*vars)->line);
				(*vars)->line = NULL;
				(*vars)->line = temp->cmd;
			}
			if((*vars)->split_args != NULL)
			{
				free((*vars)->split_args);
				(*vars)->split_args = NULL;
			}
			ft_split_args(vars);
			(*vars)->cmd_list = str_split_pipes(temp->cmd);
//			while_funcs(vars, var);
			temp = (*vars)->var.root;
			if (temp->left->right_two != NULL)
			{
				temp = (*vars)->var.root->left->right_two;
				if ((*vars)->line2 != NULL)
				{
					free((*vars)->line2);
					(*vars)->line2 = NULL;
					(*vars)->line2 = temp->cmd;
				}
				else
					(*vars)->line2 = temp->cmd;
//				if((*vars)->split_args2 != NULL)
//				{
//					free((*vars)->split_args2);
//					(*vars)->split_args2 = NULL;
//				}
				ft_split_args2(vars);
				(*vars)->cmd_list2 = str_split_pipes(temp->cmd);
				while_funcs(vars, var);
			}
		}
	}
	else if (temp->left != NULL && (ft_strcmp(temp->left->cmd, "|") == 0 || ft_strcmp(temp->left->cmd, ";") == 0))
	{
		if (temp->left->left_two != NULL)
			temp = temp->left->left_two;
	}
	else if (temp->left != NULL)
	{
		temp = temp->left;
		(*vars)->cmd_list = str_split_pipes(temp->cmd);
		while_funcs(vars, var);
	}
//	printf("TOTO\n");
//	printf("temp->cmd %s\n", temp->cmd);
	i = 0;
	if ((*vars)->cmd_list != NULL)
	{
		while ((*vars)->cmd_list[i] != NULL)
		{
			printf("(*vars)->cmd_list[i] %s\n", (*vars)->cmd_list[i]);
			i++;
		}
	}
	if ((*vars)->cmd_list2 != NULL)
	{
		i = 0;
		while ((*vars)->cmd_list2[i] != NULL)
		{
			printf("(*vars)->cmd_list2[i] %s\n", (*vars)->cmd_list2[i]);
			i++;
		}
	}
//	while (temp != NULL)
//	{
//		while_funcs(vars, var);
//	}
//	return (0);
//	while (ft_command(vars))
//	{
//		while_funcs(vars, var);
//	}
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
	/*	if (vars->split_args2 != NULL)
	{
		free(vars->split_args2);
		vars->split_args2 = NULL;
	}
	if (vars->command2 != NULL)
	{
		free(vars->command2);
		vars->command2 = NULL;
		}*/
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
		vars.zero_backup = dup(0);
		vars.one_backup = dup(1);
		if (vars.line != NULL)
		{
			ft_split_args(&temp2);
			vars.list = split_pipe_and(vars.line);
			create_tree(&(vars.list), &(vars.var));
			while_tree(&temp2, &temp);
//			while_funcs(&temp2, &temp);
			main_body(&vars);
		}
		ft_putstr("$> ");
	}
	return (0);
}
