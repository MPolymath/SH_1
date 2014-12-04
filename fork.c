/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/12 16:52:19 by mdiouf            #+#    #+#             */
/*   Updated: 2014/12/04 19:53:33 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

/*void	ft_fork2(t_main **vars, t_paths **var)
{
	
}*/

void	ft_fork(t_main **vars, t_paths **var)
{
	int	pid;
	int	i;

	if ((*vars)->type == 2)
		pipe((*vars)->pipe_fd);
	i = 0;
	if (ft_strcmp((*vars)->command, "exit") == 0)
		exit(0);
	pid = fork();
	if (pid == 0)
		execute(vars, var);
	else if (pid > 0)
	{
		wait(NULL);
		if ((*vars)->type == 2)
		{
			dup2(((*vars)->pipe_fd)[0], 0);
			close(((*vars)->pipe_fd)[1]);
			pid = fork();
			i = 0;
			if ((*vars)->line2 != NULL)
			{
				printf("line2: %s\n", (*vars)->line2);
				printf("command2: %s\n", (*vars)->command2);
				while (((*vars)->split_args2)[i] != NULL)
				{
					printf("split_args2[%d] %s\n", i, (*vars)->split_args2[i]);
					i++;
				}
				i = 0;
				(*vars)->line = (*vars)->line2;
				(*vars)->command = (*vars)->command2;
				(*vars)->split_args = (*vars)->split_args2;
				printf("line: %s\n", (*vars)->line);
				printf("command: %s\n", (*vars)->command);
				while (((*vars)->split_args)[i] != NULL)
				{
					printf("split_args[%d] %s\n", i, (*vars)->split_args[i]);
					i++;
				}
			}
			if ((pid == 0))
				execute(vars, var);
			else if (pid != 0)
			{
				wait(NULL);
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
		}
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
	else
		ft_putstr("Fork Error\n");
}
