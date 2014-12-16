/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/12 16:52:19 by mdiouf            #+#    #+#             */
/*   Updated: 2014/12/16 08:00:57 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void	if_line2(t_main **vars, int *i)
{
//	printf("line2: %s\n", (*vars)->line2);
//	printf("command2: %s\n", (*vars)->command2);
	while (((*vars)->split_args2)[*i] != NULL)
	{
//		printf("split_args2[%d] %s\n", *i, (*vars)->split_args2[*i]);
		(*i)++;
	}
	*i = 0;
	(*vars)->line = (*vars)->line2;
	(*vars)->command = (*vars)->command2;
	(*vars)->split_args = (*vars)->split_args2;
//	printf("line: %s\n", (*vars)->line);
//	printf("command: %s\n", (*vars)->command);
	while (((*vars)->split_args)[*i] != NULL)
	{
//		printf("split_args[%d] %s\n", *i, (*vars)->split_args[*i]);
		(*i)++;
	}
}

void	reset_in_out(t_main **vars)
{
	(*vars)->type = 0;
	close(0);
	close(((*vars)->pipe_fd)[0]);
	dup2((*vars)->zero_backup, 0);
	close((*vars)->zero_backup);
	close(1);
	close(((*vars)->pipe_fd)[1]);
	dup2((*vars)->one_backup, 1);
	close((*vars)->one_backup);
}

void	if_pipe(t_main **vars, t_paths **var, int *pid)
{
	int	i;
//	int	pipe[2];

	i = 0;
//	pipe[0] = dup((*vars)->pipe_fd[0]);
//	pipe[1] = dup((*vars)->pipe_fd[1]);
//	pipe = pipe;
	if ((*vars)->type == 2 || (*vars)->type == 3)
	{
//		if ((*vars)->next_pipe == 1 && (*vars)->type == 2)
//		{
//			dup2(((*vars)->pipe_fd)[1], 1);
//			close(((*vars)->pipe_fd)[0]);
//		}
//		if ((*vars)->next_pipe == 0)
//		{
		printf("BLABLABLABLABLALBALBALBALLAB\n");
		printf("vars->type %d\n", (*vars)->type);
		if ((*vars)->next_pipe == 1)
		{
			dup2(((*vars)->pipe_fd)[0], 0);
//			dup2(1, ((*vars)->pipe_fd2[1]));
//			close(((*vars)->pipe_fd2)[0]);
//			close(0);
		}
		else
			dup2(((*vars)->pipe_fd)[0], 0);
		close(((*vars)->pipe_fd)[1]);
//		if ((*vars)->next_pipe == 1)
//		{
//			printf("OKOKOKOKOOKOOKOKOKOOK\n");
//			dup2(1, ((*vars)->pipe_fd2)[1]);
//			dup2(((*vars)->pipe_fd2)[1], 1);
//			close(((*vars)->pipe_fd2)[0]);
//			close(0);
//		}
//		((*vars)->pipe_fd)[1] = pipe[1];
//		dup2(((*vars)->pipe_fd)[1], 1);
//		close(((*vars)->pipe_fd)[0]);
//		}
		*pid = fork();
		i = 0;
		if ((*vars)->line2 != NULL)
			if_line2(vars, &i);
		if ((*pid == 0))
			execute(vars, var);
		else if (*pid != 0)
		{
//			((*vars)->pipe_fd)[0] = pipe[0];
//			((*vars)->pipe_fd)[1] = pipe[1];
//			dup2(((*vars)->pipe_fd)[1], 1);
//			close(((*vars)->pipe_fd)[0]);
//			close(1);
			wait(NULL);
//			dup2((*vars)->pipe_fd2[1], 0); start;
//			close((*vars)->pipe_fd2[0]);
//			printf("THISISWHERE I NEED TO GET IT\n");
//			printf("vars->type: %d\n", (*vars)->type);
//			printf("vars->next_pipe: %d\n", (*vars)->next_pipe);
//			if ((*vars)->next_pipe == 0) // added
//				reset_in_out(vars);
//			if ((*vars)->next_pipe == 1)
//				(*vars)->type = 3;
//			if ((*vars)->type == 3)
//			{
//				printf("Test\n");
//				ft_next(vars);
//				if ((*vars)->temp != NULL)
//				{
//					dup2(1, (*vars)->pipe_fd2[1]); comment
//					close((*vars)->pipe_fd2[0]); comment
					set_line_args_cmd(vars, &((*vars)->temp));
					printf("(*vars)->line: %s\n", (*vars)->line);
					printf("(*vars)->cmd: %s\n", (*vars)->command);
					i = 0;
					while ((*vars)->split_args[i] != NULL)
					{
						printf("(*vars)->split_args[%d]: %s\n", i, (*vars)->split_args[i]);
						i++;
					}
					(*vars)->next_pipe = 2;
					*pid = fork();
					if ((*pid == 0))
					{
						execute(vars, var);
					}
					else if (*pid != 0)
					{
						wait(NULL);
					}
				}
				(*vars)->type = 0;
				printf("NULL\n");
//				set_line2_args2_cmd2(vars, &((*vars)->temp));
//				if_pipe(vars, var, &(*pid));
			}
//		}
//	}
}

void	env_restore(t_main **vars)
{
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

void	ft_fork(t_main **vars, t_paths **var)
{
	int		pid;
	int		save;
//	char	*next_priority;

	save = 0;
//	next_priority = 0;
	if (ft_strcmp((*vars)->command, "exit") == 0)
		exit(0);
	while ((*vars)->temp != NULL)
	{
		printf("(*vars)->type: %d\n", (*vars)->type);
		if ((*vars)->type == 2 || (*vars)->next_pipe == 1 || (*vars)->previous_pipe == 1)
		{
			printf("Test vars->pipe_fd \n");
			printf("Save %d: \n", save);
			pipe((*vars)->pipe_fd);
		}
		if ((save != 0)  && ((*vars)->next_pipe != 1))
		{
			printf("TEST22222\n");
			printf("Save %d: \n", save);
			if ((*vars)->previous_pipe == 1)
				dup2(save, ((*vars)->pipe_fd)[0]);
//			else
//				dup2(save, 0);
		}
		else if ((save != 0 && (*vars)->next_pipe == 1)) // added next_pipe=
		{
			printf("TEST33333\n");
			dup2(save, ((*vars)->pipe_fd)[0]);
//			close(1);
		}
		else if ((save == 0) && (*vars)->type != 2)
		{
			printf("TEST444444\n");
			dup2(((*vars)->pipe_fd)[0], 0);
//			close(((*vars)->pipe_fd)[1]);
//			close(1);
		}

//		dup2(((*vars)->pipe_fd)[0], save);
//		if ((*vars)->next_pipe == 1)
//		{
//			pipe((*vars)->pipe_fd2);
//		}
		pid = fork();
		if (pid == 0)
		{
			printf("TOTO\n");
			execute(vars, var);
		}
		else if (pid > 0)
		{
			wait(NULL);
			if ((*vars)->next_pipe == 1)
				(*vars)->previous_pipe = 1;
			else if ((*vars)->next_pipe == 0)
				(*vars)->previous_pipe = 0;
			if ((save == 0) && (*vars)->type == 2)
			{
				close(((*vars)->pipe_fd)[1]);
				if ((*vars)->type == 2 || (*vars)->next_pipe == 1)
					save = (*vars)->pipe_fd[0];
				printf("save ====== 0000000000\n");
			}
			else if ((save != 0 && (*vars)->next_pipe == 1)) // added next_pipe=
			{
				close(((*vars)->pipe_fd)[1]);
//				close(save);
				save = (*vars)->pipe_fd[0];
				printf("PPPPPPPIPPPPPPPE 2: %d\n", save);
				printf("save !!!=== 0000000000\n");
			}
			else if ((*vars)->previous_pipe == 1)
			{
				close(((*vars)->pipe_fd)[1]);
//				close(save);
				save = (*vars)->pipe_fd[0];
				printf("PPPPPPPIPPPPPPPE 2: %d\n", save);
				printf("save ======== 0000000000 && YEAAAAAA!!!");
			}
			else
			{
//				close(((*vars)->pipe_fd)[1]);
				printf("TESTINGGGGGG!!!!\n");
				close(save);
				save = 0;
			}
//			dup2(((*vars)->pipe_fd)[0], 0);
/*
		while ((*vars)->type == 3 || (*vars)->type == 2)
		{
			printf("ERF\n");
//			pid = fork();
//			if (pid == 0)
0//			{
//				printf("TEST2\n");
//				dup2(((*vars)->pipe_fd)[1], 1);
//				close(((*vars)->pipe_fd)[0]);
//				printf("TEST3\n");
				if_pipe(vars, var, &pid);
//				printf("TEST4\n");
//			}
//			else if (pid > 0)
//			{
//				wait(NULL);
//				printf("TEST5\n");
//			}
			if ((*vars)->type == 3)
				printf("TYPE: %d\n", (*vars)->type);
		}
*/
			if ((*vars)->temp_env != NULL)
			{
				env_restore(vars);
			}
//			printf("vars next pipe %d\n", (*vars)->next_pipe);
//			printf("temp->cmd: %s\n", (*vars)->temp->cmd);
//			ft_next(vars);
			if ((*vars)->type != 2)
			{
				printf("RESET ZERO\n");
				(*vars)->next_pipe = 0;
			}
			printf("(*vars)->typeooo: %d\n", (*vars)->type);
			if ((*vars)->type != 2)
				ft_next(vars);
			if ((*vars)->temp != NULL)
			{
				set_line_args_cmd(vars, &(*vars)->temp);
				printf("temp->cmd: %s\n", (*vars)->temp->cmd);
			}
			else
			{
				printf("NULL\n");
			}
			printf("NEXT PIPEEEEEEEE: %d\n", (*vars)->next_pipe);
//			reset_in_out(vars);
			close(1);
			close(0);
			dup2((*vars)->one_backup, 1);
			dup2((*vars)->zero_backup, 0);
			(*vars)->one_backup = dup(1);
			(*vars)->zero_backup = dup(0);
//			if ((*vars)->next_pipe != 1)
//				save = 0;
			(*vars)->type = 0;
		}
		else
			ft_putstr("Fork Error\n");
	}
}
