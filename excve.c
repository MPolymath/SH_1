/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/12 13:38:02 by mdiouf            #+#    #+#             */
/*   Updated: 2014/12/16 08:00:37 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"
#include <stdio.h>

void		exec_others_cmd(t_main **vars)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((*vars)->paths != NULL)
	{
		if (execve((*vars)->command, (*vars)->split_args, (*vars)->env) == -1)
		{
			while ((*vars)->paths[i] != '\0')
			{
				if ((*vars)->test_path != NULL)
				{
					free((*vars)->test_path);
					(*vars)->test_path = NULL;
				}
				(*vars)->test_path =
							ft_strjoin((*vars)->paths[i], (*vars)->command);
				printf("test_path: %s\n", (*vars)->test_path);
				if (ft_strcmp((*vars)->test_path, "/usr/bin/wc") == 0)
				{
					while ((*vars)->split_args[j] != NULL)
					{
						printf("split[%d] :%s\n", j, (*vars)->split_args[j]);
						j++;
					}
					j = 0;
					while (((*vars)->env)[j] != NULL)
					{
						printf("env[%d] %s\n",j ,((*vars)->env)[j]);
						j++;
					}
				}
				execve((*vars)->test_path, (*vars)->split_args, (*vars)->env);
				i++;
			}
			ft_putstr((*vars)->command);
			ft_putstr(": command not found\n");
			exit(0);
		}
	}
}

void		execute(t_main **vars, t_paths **var)
{
//	printf("(*vars)->type: %d", (*vars)->type);
	if ((*vars)->next_pipe == 1 || (*vars)->type == 2)
	{
//		if ((*vars)->next_pipe == 1 && (*vars)->type == 2)
//		{
//			dup2(((*vars)->pipe_fd)[1], (*vars)->pipe_fd2)[1]);
//			close(((*vars)->pipe_fd)[0]);
//		}
//		else
		printf("command: %s\n", (*vars)->command);
//		close(1);
		printf("PIPE #: %d\n", (*vars)->pipe_fd[0]);
		dup2(((*vars)->pipe_fd)[1], 1);
		close(((*vars)->pipe_fd)[0]);
		printf("SUPERHERO!!!!!\n");
//		printf("TEST3333\n");
	}
	else if ((*vars)->previous_pipe == 1 && (*vars)->next_pipe == 0)
	{
		printf("PIPE #: %d\n", (*vars)->pipe_fd[1]);
		dup2(((*vars)->pipe_fd)[0], 0);
		close(((*vars)->pipe_fd)[1]);
	}
//	else if ((*vars)->next_pipe == 0 && save != 0)
//	{
//	}
//	printf("(*vars)->type: %d", (*vars)->type);
	if (ft_strcmp((*vars)->command, "cd") == 0)
		cd_cmd(vars, var);
	else if (ft_strcmp((*vars)->command, "setenv") == 0)
		setenv_cmd(vars);
	else if (ft_strcmp((*vars)->command, "unsetenv") == 0)
		unsetenv_cmd(vars);
	else if (ft_strcmp((*vars)->command, "env") == 0)
		env_cmd(vars, var);
	else
		exec_others_cmd(vars);
}
