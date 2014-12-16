/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/06 17:17:43 by mdiouf            #+#    #+#             */
/*   Updated: 2014/12/16 07:13:33 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"
#include "get_next_line.h"

// need to dup2 and pipe fd[1] for | handling get new command using ft_next
// create temporary variable that keeps original temp
// if new temp cmd == | then need to do the duping else don't

void		init_main(t_main *vars, int argc, char **argv)
{
	vars->fd = 0;
	vars->args_nbr = 0;
	vars->i = 0;
	vars->next_pipe = 0;
	vars->previous_pipe = 0;
	vars->env = NULL;
	vars->temp_env = NULL;
	vars->line = NULL;
	vars->line2 = NULL;
	vars->tmp = NULL;
	vars->tmp2 = NULL;
	vars->cmd_list = NULL;
	vars->cmd_list2 = NULL;
	vars->command = NULL;
	vars->command2 = NULL;
	vars->test_path = NULL;
	vars->paths = NULL;
	vars->split_args = NULL;
	vars->split_args2 = NULL;
	argc = argc;
	argv = argv;
	ft_putstr("$> ");
}

void		ft_next(t_main **vars)
{
	t_tree	*temp2;

	printf("ft_next\n");
	temp2 = NULL;
	if ((*vars)->var.root->child == 1)
	{
		(*vars)->temp = NULL;
		 return ;
	}
	else if ((*vars)->var.root->child == 2)
	{
		(*vars)->temp = NULL;
		return ;
	}
	else if ((*vars)->var.root->child == 3)
	{
		if ((*vars)->temp == (*vars)->var.root->left->right_two)
			(*vars)->temp = NULL;
		else
			(*vars)->temp = (*vars)->var.root->left->right_two;
		return ;
	}
	else if ((*vars)->var.root->child > 3)
	{
		temp2 = (*vars)->var.root->right_next;
		if ((*vars)->temp == (*vars)->var.root->left->right_two && (ft_strcmp(temp2->cmd, "|") == 0 || ft_strcmp(temp2->cmd, ";") == 0))
		{
			if (ft_strcmp(temp2->cmd, "|") == 0 && (*vars)->type == 2)
			{
				printf("VARS NEXT PIPE\n");
				(*vars)->next_pipe = 1;
			}
			(*vars)->temp = temp2->right_two;
			return ;
		}

//		printf("temp2->cmd: %s\n", temp2->cmd);
//		printf("temp2->right_two->cmd %s\n", temp2->right_two->cmd);
		if (ft_strcmp(temp2->cmd, "|") != 0 && ft_strcmp(temp2->cmd, ";") != 0)
		{
			(*vars)->temp = temp2;
			return ;
		}
		while (temp2 != NULL)
		{
			if ((*vars)->temp == temp2)
			{
//				(*vars)->temp = temp2->left;
				(*vars)->temp = temp2->right_two;
				return ;
			}
			else if ((*vars)->temp == temp2->right_two)
			{
//				if (temp2->right_next != NULL && ft_strcmp(temp2->right_next->cmd, "|") == 0)
//					(*vars)->next_pipe = 1;
				(*vars)->temp = temp2->right_next;
				return ;
			}
			else
				temp2 = temp2->right_next;
//			else if ((*vars)->temp == temp2->right)
//			{
//				(*vars)->temp = temp2->right_next;
//				return ;
//			}
			if (temp2 == NULL)
				printf("NULL\n");
			else
			printf("NOT\n");
		}
		if (temp2 == NULL)
		{
			ft_putstr_fd("Erreur Next Command Not In Tree\n", 2);
			exit(0);
		}
//		printf("cmd: %s\n", (*vars)->temp->cmd);
	}
}

void		while_funcs(t_main **vars, t_paths **var)
{
	printf("while_funcs\n");
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

void		handle_and1(t_main **vars, t_paths **var, t_tree **temp)
{
	*temp = (*temp)->left->left_two;
	if ((*vars)->line != NULL)
	{
		free((*vars)->line);
		(*vars)->line = NULL;
		(*vars)->line = (*temp)->cmd;
	}
	if ((*vars)->split_args != NULL)
	{
		free((*vars)->split_args);
		(*vars)->split_args = NULL;
	}
	ft_split_args(vars);
	(*vars)->cmd_list = str_split_pipes((*temp)->cmd);
	while_funcs(vars, var);
}

void		handle_and2(t_main **vars, t_paths **var, t_tree **temp)
{
	*temp = (*vars)->var.root;
	if ((*temp)->left->right_two != NULL)
	{
		*temp = (*vars)->var.root->left->right_two;
		if ((*vars)->line != NULL)
		{
			free((*vars)->line);
			(*vars)->line = NULL;
			(*vars)->line = (*temp)->cmd;
		}
		if ((*vars)->split_args != NULL)
		{
			free((*vars)->split_args);
			(*vars)->split_args = NULL;
		}
		ft_split_args(vars);
		(*vars)->cmd_list = str_split_pipes((*temp)->cmd);
		while_funcs(vars, var);
	}
}

void		handle_and(t_main **vars, t_paths **var, t_tree **temp)
{
	printf("handle_and\n");
	(*vars)->type = 1;
	if ((*temp)->left->left_two != NULL)
	{
		handle_and1(vars, var, temp);
		handle_and2(vars, var, temp);
	}
}

void		set_line2_args2_cmd2(t_main **vars, t_tree **temp)
{
	if ((*vars)->line2 != NULL)
	{
		free((*vars)->line2);
		(*vars)->line2 = NULL;
		(*vars)->line2 = (*temp)->cmd;
	}
	else
		(*vars)->line2 = (*temp)->cmd;
	ft_split_args2(vars);
	(*vars)->cmd_list2 = str_split_pipes((*temp)->cmd);
}

void		handle_pipe2(t_main **vars, t_paths **var, t_tree **temp)
{
	t_tree	*temporary;

	temporary = NULL;
	*temp = (*vars)->var.root;
	if ((*temp)->left->right_two != NULL)
	{
		*temp = (*vars)->var.root->left->right_two;
		set_line2_args2_cmd2(vars, temp);
		if ((*vars)->var.root->child > 3)
		{
			temporary = (*vars)->temp;
			ft_next(vars);
//			printf("temp: %s\n", (*vars)->temp->cmd);
			(*vars)->temp = temporary;
		}
		while_funcs(vars, var);
	}
}

void		set_line_args_cmd(t_main **vars, t_tree **temp)
{
	if ((*vars)->line != NULL)
	{
		free((*vars)->line);
		(*vars)->line = NULL;
		(*vars)->line = (*temp)->cmd;
	}
	if ((*vars)->split_args != NULL)
	{
		free((*vars)->split_args);
		(*vars)->split_args = NULL;
	}
	ft_split_args(vars);
	(*vars)->cmd_list = str_split_pipes((*temp)->cmd);
}

void		handle_pipe1(t_main **vars, t_tree **temp)
{
	*temp = (*temp)->left->left_two;
	set_line_args_cmd(vars, temp);
//	while_funcs(vars, var);
}

void		handle_pipe(t_main **vars, t_paths **var, t_tree **temp)
{
	printf("handle_pipe\n");
	(*vars)->type = 2;
	if ((*temp)->left->left_two != NULL)
	{
		handle_pipe1(vars, temp);
		handle_pipe2(vars, var, temp);
	}
}

void		print_command_lists(t_main **vars, int *i)
{
	*i = 0;
//	printf("print_command_lists\n");
	if ((*vars)->cmd_list != NULL)
	{
		while ((*vars)->cmd_list[*i] != NULL)
		{
//			printf("(*vars)->cmd_list[i] %s\n", (*vars)->cmd_list[*i]);
			(*i)++;
		}
	}
	if ((*vars)->cmd_list2 != NULL)
	{
		*i = 0;
		while ((*vars)->cmd_list2[*i] != NULL)
		{
//			printf("(*vars)->cmd_list2[i] %s\n", (*vars)->cmd_list2[*i]);
			(*i)++;
		}
	}
}

void		init_while_tree(t_main **vars, t_tree **temp, int *i)
{
	*i = 0;
	(*vars)->pipe_fd[0] = -1;
	(*vars)->pipe_fd[1] = -1;
	*temp = (*vars)->var.root; // initialise to first command
	(*vars)->type = 0;
}

void		while_tree_body(t_main **vars, t_paths **var)
{
	if (ft_strcmp(((*vars)->temp)->left->cmd, ";") == 0) // ; handling
		handle_and(vars, var, &((*vars)->temp));
	else if (ft_strcmp((*vars)->temp->left->cmd, "|") == 0)
		handle_pipe(vars, var, &(*vars)->temp);
	else if ((*vars)->temp->left != NULL && (ft_strcmp((*vars)->temp->left->cmd, "|") == 0 ||
			ft_strcmp((*vars)->temp->left->cmd, ";") == 0))
	{
		if ((*vars)->temp->left->left_two != NULL)
			(*vars)->temp = (*vars)->temp->left->left_two;
	}
	else if ((*vars)->temp->left != NULL)
	{
		(*vars)->temp = (*vars)->temp->left;
		(*vars)->cmd_list = str_split_pipes((*vars)->temp->cmd);
		while_funcs(vars, var);
	}
}

void		free_all(t_main **vars)
{
	if ((*vars)->command != NULL)
	{
		printf("TEST\n");
		free((*vars)->command);
		(*vars)->command = NULL;
	}
	if ((*vars)->split_args != NULL)
	{
		printf("TEST1\n");
		free((*vars)->split_args);
		(*vars)->split_args = NULL;
	}
	if ((*vars)->cmd_list != NULL)
	{
		printf("TEST2\n");
		free((*vars)->cmd_list);
		(*vars)->cmd_list = NULL;
	}
	if ((*vars)->line != NULL)
	{
		printf("TEST3\n");
		free((*vars)->line);
		(*vars)->line = NULL;
	}
//	if ((*vars)->command2 != NULL)
//	{
//		printf("TEST4\n");
//		free((*vars)->command2);
//		(*vars)->command2 = NULL;
//	}
//	if ((*vars)->split_args2 != NULL)
//	{
//		printf("TEST5\n");
//		free((*vars)->split_args2);
//		(*vars)->split_args2 = NULL;
//	}
	if ((*vars)->cmd_list2 != NULL)
	{
		printf("TEST6\n");
		free((*vars)->cmd_list2);
		(*vars)->cmd_list2 = NULL;
	}
//	if ((*vars)->line2 != NULL)
//	{
//		printf("TEST7\n");
//		free((*vars)->line2);
//		(*vars)->line2 = NULL;
//	}
}

void		loop_smpl_cmd(t_main **vars/*, t_paths **var*/)
{
	free_all(vars);
}

void		loop_pipe_cmd(t_main **vars/*, t_paths **var*/)
{
	printf("loop_pipe_cmd\n");
	free_all(vars);
}

void		loop_and_cmd(t_main **vars/*, t_paths **var*/)
{
	free_all(vars);
}

void		loops_choice(t_main **vars)
{
	printf("loops_choice\n");
	if (ft_strcmp((*vars)->temp->cmd, ";") == 0)
		loop_and_cmd(vars/*, var*/);
	else if (ft_strcmp((*vars)->temp->cmd, "|") == 0)
		loop_pipe_cmd(vars/*, var*/);
	else
		loop_smpl_cmd(vars/*, var*/);
}

void		while_tree(t_main **vars, t_paths **var)
{
	int		i;

	printf("while_tree\n");
	init_while_tree(vars, &((*vars)->temp), &i);
	while_tree_body(vars, var);
	while ((*vars)->temp != NULL)
	{
		ft_next(vars);
		if ((*vars)->temp != NULL)
		{
//			printf("cmd: %s\n", (*vars)->temp->cmd);
			loops_choice(vars);
		}
	}
	print_command_lists(vars, &i);
}

// leftovers from above function
//	while (temp != NULL)
//	{
//		while_funcs(vars, var);
//	}
//	return (0);
//	while (ft_command(vars))
//	{
//		while_funcs(vars, var);
//	}

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

int			init_main1(t_mn *vr, char **envp)
{
	vr->temp = &(vr->var);
	vr->temp2 = &(vr->vars);
	if (envp[0] == NULL)
	{
		ft_putstr_fd("Program cannot run without env\n", 2);
		return (-1);
	}
	return (0);
}

int			main(int argc, char **argv, char **envp)
{
	t_mn	vr;

	if (init_main1(&vr, envp) == -1)
		return (0);
	init_main(&(vr.vars), argc, argv);
	cpy_env(envp, &(vr.vars));
	vr.vars.paths = ft_split_path(envp, &(vr.vars.env));
	while (get_next_line(vr.vars.fd, &(vr.vars.line)))
	{
		vr.vars.zero_backup = dup(0);
		vr.vars.one_backup = dup(1);
		if (vr.vars.line != NULL)
		{
			ft_split_args(&(vr.temp2));
			vr.vars.list = split_pipe_and(vr.vars.line);
			create_tree(&(vr.vars.list), &(vr.vars.var));
			while_tree(&(vr.temp2), &(vr.temp));
//			while_funcs(&(vr.temp2), &(vr.temp));
			main_body(&(vr.vars));
		}
		ft_putstr("$> ");
	}
	return (0);
}
